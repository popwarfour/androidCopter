// --------- ANDROID PROTOCOL -----------
extern int SPEED_INDEX = 0;
extern int GYRO_X_INDEX = 1;
extern int GYRO_Y_INDEX = 2;
extern int GYRO_Z_INDEX = 3;

// --------- MOTOR CONSTANTS ------------
extern int maxSpeed = 78;
extern int minSpeed = 4;

extern float motor1Speed = 0;
extern float motor2Speed = 0;
extern float motor3Speed = 0;
extern float motor4Speed = 0;

extern float PIDroll_val = 0;
extern float PIDpitch_val = 0;
extern float PIDyaw_val = 0;


// --------- SENSOR VALUES ------------
extern float rollSensor = 0;
extern float pitchSensor = 0;
extern float yawSensor = 0;

// --------- STEERING VALUES ------------
extern int speedSteer = 0;
extern int rollSteer = 0;
extern int pitchSteer = 0;
extern int yawSteer = 0;
extern boolean firstTimeConnecting = true;

extern boolean lightOn = false;


//-------PID Config----------

#define ROLL_PID_KP  10.0
#define ROLL_PID_KI  1.0
#define ROLL_PID_KD  10.0
#define ROLL_PID_MIN  -50.0
#define ROLL_PID_MAX  50.0

#define PITCH_PID_KP  10.0
#define PITCH_PID_KI  1.0
#define PITCH_PID_KD  10.0
#define PITCH_PID_MIN  -50.0
#define PITCH_PID_MAX  50.0

#define YAW_PID_KP  10.0
#define YAW_PID_KI  1.0
#define YAW_PID_KD  10.0
#define YAW_PID_MIN  -50.0
#define YAW_PID_MAX  50.0


#define ANGLEX_KP 5.0
#define ANGLEX_KI 0.02
#define ANGLEX_KD -0.015
#define ANGLEX_MIN -100.0
#define ANGLEX_MAX 100.0

#define ANGLEY_KP 5.0
#define ANGLEY_KI 0.02
#define ANGLEY_KD -0.015
#define ANGLEY_MIN -100.0
#define ANGLEY_MAX 100.0

