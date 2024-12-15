 
 
Development of a Student Attendance System with Face Recognition 
 
 
Student Name: Necmiye Soylu 
Student ID: 241805111 
# 1. Introduction 

Attendance tracking is a crucial aspect of educational institutions. Manual methods are prone to errors and inefficiencies. This project introduces an automated Student Attendance Systemleveraging face recognition technology for accurate and efficient tracking. The system will utilize a camera mounted on a servo motor to scan the environment for student faces, ensuring dynamic coverage of the classroom. 

### 1.1 Objectives 

To develop a reliable attendance system using face recognition. 
To automate the scanning process with a camera mounted on a servo motor. 
To minimize manual intervention and errors in attendance tracking. 
 
# 2. Technical Background 

### 2.1 Face Recognition Technology 

Face recognition uses image processing and machine learning techniques to identify individuals based on facial features. OpenCV and pre-trained deep learning models like FaceNet or Dlib can be utilized for this purpose. 

### 2.2 Hardware Components 

Camera: Captures images of students for processing. 
Servo Motor: Enables the camera to rotate and scan the room. 
Microcontroller: Coordinates hardware and processes data. 
# 3. Design and Development 

### 3.1 Hardware 

Camera: A high-definition webcam capable of capturing clear images in varying light conditions. 
Servo Motor: Allows 180-degree rotation to cover a larger area. Controlled via PWM (Pulse Width Modulation). 
Microcontroller: Raspberry Pi or Arduino for integrating camera and servo motor. 
Power Supply: A 5V power source for the microcontroller and peripherals. 

### 3.2 Software 

Face Recognition Algorithm: 
OpenCV for real-time face detection. 
Pre-trained models for face identification. 
Servo Control: A program to move the camera incrementally and scan the environment. 
Database Integration: Logs attendance records in a database with timestamps. 
3.3 Workflow 

The system scans the classroom using the rotating camera. 
Faces are detected and identified using the recognition algorithm. 
Attendance is marked automatically in a database 

# 4. Expected Outcomes 

A functional prototype demonstrating automated attendance logging. 
Improved accuracy and efficiency in attendance tracking. 
Detailed documentation covering the design, development, and testing process. 
 
	 
 					 
  
**Component**  **Description** **Quantity** 

Camera            HD webcam        1 

Servo Motor       SG90 Servo Motor 1 

Microcontroller    Raspberry Pi 4  1 
 