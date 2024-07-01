import cv2
import numpy as np
import mediapipe as mp
import socket

def main():
    server_address_port = ("192.168.9.106", 20001)
    buffer_size = 1024
    udp_client_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    mp_face_mesh = mp.solutions.face_mesh
    left_eye_indices = [362, 382, 381, 380, 374, 373, 390, 249, 263, 466, 388, 387, 386, 385, 384, 398]
    right_eye_indices = [33, 7, 163, 144, 145, 153, 154, 155, 133, 173, 157, 158, 159, 160, 161, 246]
    left_iris_indices = [474, 475, 476, 477]
    right_iris_indices = [469, 470, 471, 472]

    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("Error: Could not open video capture device.")
        return

    with mp_face_mesh.FaceMesh(max_num_faces=1, refine_landmarks=True, min_detection_confidence=0.5, min_tracking_confidence=0.5) as face_mesh:
        while True:
            ret, frame = cap.read()
            if not ret:
                print("Error: Could not read frame from video device.")
                break

            frame = cv2.flip(frame, 1)
            rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            results = face_mesh.process(rgb_frame)
            if results.multi_face_landmarks:
                process_face_landmarks(frame, results, left_eye_indices, right_eye_indices, left_iris_indices, right_iris_indices, udp_client_socket, server_address_port, buffer_size)

            cv2.imshow('Eye-Controlled Robot Car', frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    cap.release()
    cv2.destroyAllWindows()
    udp_client_socket.close()

def process_face_landmarks(frame, results, left_eye, right_eye, left_iris, right_iris, socket, address, buffer_size):
    img_h, img_w = frame.shape[:2]
    mesh_points = np.array([np.multiply([p.x, p.y], [img_w, img_h]).astype(int) for p in results.multi_face_landmarks[0].landmark])

    # Detect eyes and draw rectangles
    xl, yl, wl, hl = cv2.boundingRect(mesh_points[left_eye])
    xr, yr, wr, hr = cv2.boundingRect(mesh_points[right_eye])
    cv2.rectangle(frame, (xl, yl), (xl + wl, yl + hl), (0, 255, 0), 1)
    cv2.rectangle(frame, (xr, yr), (xr + wr, yr + hr), (0, 255, 0), 1)

    # Detect iris and center point
    l_cx, l_cy = compute_iris_center(mesh_points[left_iris])
    r_cx, r_cy = compute_iris_center(mesh_points[right_iris])
    cv2.circle(frame, (l_cx, l_cy), 2, (0, 0, 255), -1)  # Red dot at the iris center
    cv2.circle(frame, (r_cx, r_cy), 2, (0, 0, 255), -1)

    # Determine eye gaze direction and send command
    command = determine_gaze_command(l_cx, l_cy, xl, yl, wl, hl)
    print(command)  # Debug output
    send_command(command, socket, address, buffer_size)

def compute_iris_center(iris_points):
    center = np.mean(iris_points, axis=0).astype(int)
    return center

def determine_gaze_command(cx, cy, x, y, w, h):
    if y + h/3 < cy < y + 2*h/3:
        if x + w/3 < cx < x + 2*w/3:
            return "Center"
        elif cx < x + w/3:
            return "Left"
        else:
            return "Right"
    elif cy < y + h/3:
        if x + w/3 < cx < x + 2*w/3:
            return "Up"
        elif cx < x + w/3:
            return "Upper Left"
        else:
            return "Upper Right"
    else:
        if x + w/3 < cx < x + 2*w/3:
            return "Down"
        elif cx < x + w/3:
            return "Left Down"
        else:
            return "Right Down"

def send_command(command, socket, address, buffer_size):
    bytes_to_send = str.encode(command)
    socket.sendto(bytes_to_send, address)
    # Optionally, uncomment the next line to receive a response from the server
    # response = socket.recvfrom(buffer_size)
    # print("Received from server:", response)

if __name__ == "__main__":
    main()
