import cv2
import mediapipe as mp
import time
import math
from cvzone.SerialModule import SerialObject

cap = cv2.VideoCapture(1)

mpHands = mp.solutions.hands
hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils

pTime = 0
cTime = 0

index_x = 0
index_y = 0

thumb_x = 0
thumb_y = 0

max_i_t_pxs = 200
middle_i_t_pxs = 120
min_i_t_pxs = 50
switchoff = 30

color = ''
textColor = (0, 0, 0)

arduino = SerialObject()

while True:
    success, img = cap.read()
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(imgRGB)

    # Loop through each HAND and get HAND LANDMARKS (x, y)
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            for id, lm in enumerate(handLms.landmark):
                # print(id, lm)  # Get hand point ID and landmarks (x, y)

                # print(results.multi_hand_landmarks)

                # Get ID position in PX
                h, w, c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)

                # print(id, cx, cy)

                # Get index X/Y and thumb X/Y
                if (id == 8):
                    index_x = cx
                    index_y = cy

                if (id == 4):
                    thumb_x = cx
                    thumb_y = cy

                # Draw line between Index and Thumb (hypotenus)
                cv2.line(img, (index_x, index_y),
                         (thumb_x, thumb_y), (255, 0, 255), 2)

                # Find middle point of hypotenus
                i_m_x = int((index_x + thumb_x) / 2)
                i_m_y = int((index_y + thumb_y) / 2)

                cv2.circle(img, (i_m_x, i_m_y), 4, (255, 0, 255), 4)

                # Find length of hypotenuse, but first calc catheti
                cathet1 = abs(thumb_x - index_x)
                cathet2 = abs(index_y - thumb_y)

                hypotenuse = math.sqrt((cathet1**2) + (cathet2 ** 2))

                cv2.putText(img, str(math.trunc(hypotenuse)),
                            (i_m_x + 20, i_m_y + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 0, 255), 1)

                if int(hypotenuse) >= max_i_t_pxs:
                    color = "blu"
                    arduino.sendData([0, 0, 1])

                if int(hypotenuse) < max_i_t_pxs and int(hypotenuse) >= middle_i_t_pxs:
                    color = "verde"
                    arduino.sendData([0, 1, 0])

                if int(hypotenuse) < middle_i_t_pxs and int(hypotenuse) >= min_i_t_pxs:
                    color = "rosso"
                    arduino.sendData([1, 0, 0])

                if int(hypotenuse) < switchoff and int(hypotenuse) >= 0:
                    color = "spento"
                    arduino.sendData([0, 0, 0])

            # Draw points and connections on hands
            mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS)

    # Calc FPS
    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime

    # Print FPS
    cv2.putText(img, 'FPS ' + str(int(fps)), (10, 30),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    # Show in which color we are
    cv2.putText(img, 'Colore LED: ' + color, (10, 70),
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("Image", img)
    cv2.waitKey(1)
