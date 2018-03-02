#include "Oscillator.h"
#define SERVO_NUM 8

//Original
//  ----          ----
// | 16 |        | 14 |
//  ---- -      - ----
//      | 05  12 |
//      |        |
//      | 04  13 |
//  ---- -------- ----
// | 02 |        | 15 |
//  ----          ----
//

//My Edit
//  ----          ----
// | 06 |        | 02 |
//  ---- -      - ----
//      | 07  03 |
//      |        |
//      | 08  04 |
//  ---- -------- ----
// | 09 |        | 05 |
//  ----          ----


class Q{
  public:
    void init(int pins[SERVO_NUM]);
    void attachServos();
    void detachServos();
    void _moveServos(int time, int  servo_target[]);
    void stepServos(int  servo_target[]);
    void moveServos(int  servo_target[]);
    void execute(int servo_matrix[][SERVO_NUM+1],int steps);
    void execute_progmem(int servo_matrix[][SERVO_NUM+1],int steps);
    void home();
    void zero();
    void servo_zero();
    void start();
    void standby();
    void left_shift();
    void right_shift();
    void forward();
    void backward();
    void turn_left();
    void turn_right();
    void lie();
    void say_hi();
    void fighting();
    void push_up();
    void sleep();
    void dance1();
    void dance2();
    void dance3();
    private:
//      unsigned long final_time;
//      unsigned long partial_time;
      int servo_pins[SERVO_NUM];
      Oscillator servo[SERVO_NUM];
      int servo_position[SERVO_NUM];
//      float increment[SERVO_NUM];
  };

void Q::init(int pins[SERVO_NUM]){
    for(int i =0 ; i < SERVO_NUM; i++){
      servo_pins[i] = pins[i];
//      servo[i].attach(servo_pins[i]);
//      servo[i].SetPosition(90);
//      servo_position[i] = 90;
//      delay(1000);
//      servo[i].detach();
      }
      attachServos();
  }

void Q::attachServos(){
      for(int i =0 ; i < SERVO_NUM; i++){
        servo[i].attach(servo_pins[i]);
      }
  }
void Q::detachServos(){
      for(int i =0 ; i < SERVO_NUM; i++){
        servo[i].detach();
      }
  }


void Q::stepServos(int  servo_target[]){
      for(int i =0 ; i < SERVO_NUM; i++){
      servo[i].attach(servo_pins[i]);
      servo[i].SetPosition(servo_target[i]);
      servo_position[i] = servo_target[i];
      delay(800);
      servo[i].detach();
  }
}


void Q::moveServos(int  servo_target[]){
    for(int i =0;i<SERVO_NUM;i++){
    servo[i].SetPosition(servo_target[i]);
    }
  }
void Q::execute(int servo_matrix[][SERVO_NUM+1],int steps){
  for(int j = 0;j<steps;j++){
      moveServos(servo_matrix[j]);
      delay(servo_matrix[j][SERVO_NUM]);
    }
  }

void Q::execute_progmem(int servo_matrix[][SERVO_NUM+1],int steps){
    for(int j = 0;j<steps;j++){
      for(int i =0;i<SERVO_NUM;i++){
        servo[i].SetPosition(pgm_read_word_near(servo_matrix[j]+i));
    }
        delay(pgm_read_word_near(servo_matrix[j]+SERVO_NUM));
    }
  }

void Q::home(){
  int homes[SERVO_NUM] PROGMEM = {135,  45, 135,  45,  45, 135,  45, 135};
  stepServos(homes);
//  detachServos();
  }

void Q::zero(){
  int zeros[SERVO_NUM] PROGMEM = {90,90,90,90,90,90,90,90};
  stepServos(zeros);
  }



void Q::servo_zero(){
  int steps = 1;
  const static int servo_matrix_zero[][SERVO_NUM+1] PROGMEM = {  135,  45, 135,  45,  45, 135,  45, 135,  500  };
  execute_progmem(servo_matrix_zero,steps);  
  }


void Q::start(){
  int steps = 1;
  const static int servo_matrix_start[][SERVO_NUM+1] PROGMEM = {  90,  90, 90,  90,  90, 90,  90, 90,  500  };
  execute_progmem(servo_matrix_start,steps);  
  }


void Q::standby(){
  int steps = 2;
  const static int servo_matrix_standby[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   90,  90,  90,  90,  90,  90,  90,  90,  500  }, // servo center point
  {   70,  90,  90, 110, 110,  90,  90,  70,  500  }, // standby
};
  execute_progmem(servo_matrix_standby,steps);  
  }

void Q::forward(){
  int steps = 11;
  const static int servo_matrix_forward[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
  {   90,  90,  90, 110, 110,  90,  45,  90,  200  }, // leg1,4 up; leg4 fw
  {   70,  90,  90, 110, 110,  90,  45,  70,  200  }, // leg1,4 dn
  {   70,  90,  90,  90,  90,  90,  45,  70,  200  }, // leg2,3 up
  {   70,  45, 135,  90,  90,  90,  90,  70,  200  }, // leg1,4 bk; leg2 fw
  {   70,  45, 135, 110, 110,  90,  90,  70,  200  }, // leg2,3 dn
  {   90,  90, 135, 110, 110,  90,  90,  90,  200  }, // leg1,4 up; leg1 fw
  {   90,  90,  90, 110, 110, 135,  90,  90,  200  }, // leg2,3 bk
  {   70,  90,  90, 110, 110, 135,  90,  70,  200  }, // leg1,4 dn
  {   70,  90,  90, 110,  90, 135,  90,  70,  200  }, // leg3 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // leg3 fw dn
};
  execute_progmem(servo_matrix_forward,steps);
  }

void Q::backward(){
  int steps = 11;
  const static int servo_matrix_backward[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
  {   90,  45,  90, 110, 110,  90,  90,  90,  200  }, // leg4,1 up; leg1 fw
  {   70,  45,  90, 110, 110,  90,  90,  70,  200  }, // leg4,1 dn
  {   70,  45,  90,  90,  90,  90,  90,  70,  200  }, // leg3,2 up
  {   70,  90,  90,  90,  90, 135,  45,  70,  200  }, // leg4,1 bk; leg3 fw
  {   70,  90,  90, 110, 110, 135,  45,  70,  200  }, // leg3,2 dn
  {   90,  90,  90, 110, 110, 135,  90,  90,  200  }, // leg4,1 up; leg4 fw
  {   90,  90, 135, 110, 110,  90,  90,  90,  200  }, // leg3,1 bk
  {   70,  90, 135, 110, 110,  90,  90,  70,  200  }, // leg4,1 dn
  {   70,  90, 135,  90, 110,  90,  90,  70,  200  }, // leg2 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // leg2 fw dn
};
  execute_progmem(servo_matrix_backward,steps);  
  }

void Q::left_shift(){
  int steps = 11;
  const static int servo_matrix_left_shift[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
  {   70,  90,  45,  90,  90,  90,  90,  70,  200  }, // leg3,2 up; leg2 fw
  {   70,  90,  45, 110, 110,  90,  90,  70,  200  }, // leg3,2 dn
  {   90,  90,  45, 110, 110,  90,  90,  90,  200  }, // leg1,4 up
  {   90, 135,  90, 110, 110,  45,  90,  90,  200  }, // leg3,2 bk; leg1 fw
  {   70, 135,  90, 110, 110,  45,  90,  70,  200  }, // leg1,4 dn
  {   70, 135,  90,  90,  90,  90,  90,  70,  200  }, // leg3,2 up; leg3 fw
  {   70,  90,  90,  90,  90,  90, 135,  70,  200  }, // leg1,4 bk
  {   70,  90,  90, 110, 110,  90, 135,  70,  200  }, // leg3,2 dn
  {   70,  90,  90, 110, 110,  90, 135,  90,  200  }, // leg4 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // leg4 fw dn
};
  execute_progmem(servo_matrix_left_shift,steps);  
  }

void Q::right_shift(){
  int steps = 11;
  const static int servo_matrix_right_shift[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
  {   70,  90,  90,  90,  90,  45,  90,  70,  200  }, // leg2,3 up; leg3 fw
  {   70,  90,  90, 110, 110,  45,  90,  70,  200  }, // leg2,3 dn
  {   90,  90,  90, 110, 110,  45,  90,  90,  200  }, // leg4,1 up
  {   90,  90,  45, 110, 110,  90, 135,  90,  200  }, // leg2,3 bk; leg4 fw
  {   70,  90,  45, 110, 110,  90, 135,  70,  200  }, // leg4,1 dn
  {   70,  90,  90,  90,  90,  90, 135,  70,  200  }, // leg2,3 up; leg2 fw
  {   70, 135,  90,  90,  90,  90,  90,  70,  200  }, // leg4,1 bk
  {   70, 135,  90, 110, 110,  90,  90,  70,  200  }, // leg2,3 dn
  {   90, 135,  90, 110, 110,  90,  90,  70,  200  }, // leg1 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // leg1 fw dn
};
  execute_progmem(servo_matrix_right_shift,steps);  
  }

void Q::turn_left(){
  int steps = 8;
  const static int servo_matrix_turn_left[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
  {   90,  90,  90, 110, 110,  90,  90,  90,  200  }, // leg1,4 up
  {   90, 135,  90, 110, 110,  90, 135,  90,  200  }, // leg1,4 turn
  {   70, 135,  90, 110, 110,  90, 135,  70,  200  }, // leg1,4 dn
  {   70, 135,  90,  90,  90,  90, 135,  70,  200  }, // leg2,3 up
  {   70, 135, 135,  90,  90, 135, 135,  70,  200  }, // leg2,3 turn
  {   70, 135, 135, 110, 110, 135, 135,  70,  200  }, // leg2,3 dn
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // leg1,2,3,4 turn
};
  execute_progmem(servo_matrix_turn_left,steps);  
  }

void Q::turn_right(){
  int steps = 8;
  const static int servo_matrix_turn_right[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // standby
  {   70,  90,  90,  90,  90,  90,  90,  70,  200  }, // leg2,3 up
  {   70,  90,  45,  90,  90,  45,  90,  70,  200  }, // leg2,3 turn
  {   70,  90,  45, 110, 110,  45,  90,  70,  200  }, // leg2,3 dn
  {   90,  90,  45, 110, 110,  45,  90,  90,  200  }, // leg1,4 up
  {   90,  45,  45, 110, 110,  45,  45,  90,  200  }, // leg1,4 turn
  {   70,  45,  45, 110, 110,  45,  45,  70,  200  }, // leg1,4 dn
  {   70,  90,  90, 110, 110,  90,  90,  70,  200  }, // leg1,2,3,4 turn
};
  execute_progmem(servo_matrix_turn_right,steps);  
  }
void Q::lie(){
  int steps = 1;
  const static int servo_matrix_lie[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {  110,  90,  90,  70,  70,  90,  90, 110,  500  }, // leg1,4 up
};
  execute_progmem(servo_matrix_lie,steps);  
  }

void Q::say_hi(){
  int steps = 7;
  const static int servo_matrix_say_hi[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90,  90,  90,  90,  90,  90,  400}, // leg2,3,4 dn
  {  170,  90,  90,  90,  90,  90,  90,  90,  400}, // leg1 up
  {  170, 130,  90,  90,  90,  90,  90,  90,  400}, // leg1 left
  {  170,  50,  90,  90,  90,  90,  90,  90,  400}, // leg1 right
  {  170, 130,  90,  90,  90,  90,  90,  90,  400}, // leg1 left
  {  170,  90,  90,  90,  90,  90,  90,  90,  400}, // leg1 right
  {   70,  90,  90,  90,  90,  90,  90,  90,  400}, // leg1 dn
};
  execute_progmem(servo_matrix_say_hi,steps);  
  }

void Q::fighting(){
  int steps = 11;
  const static int servo_matrix_fighting[][SERVO_NUM+1] PROGMEM =  {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {  120,  90,  90, 110,  60,  90,  90,  70,  500  }, // leg1, 2 down
  {  120,  70,  70, 110,  60,  70,  70,  70,  500  }, // body turn left
  {  120, 110, 110, 110,  60, 110, 110,  70,  500  }, // body turn right
  {  120,  70,  70, 110,  60,  70,  70,  70,  500  }, // body turn left
  {  120, 110, 110, 110,  60, 110, 110,  70,  500  }, // body turn right
  {   70,  90,  90,  70, 110,  90,  90, 110,  500  }, // leg1, 2 up ; leg3, 4 down
  {   70,  70,  70,  70, 110,  70,  70, 110,  500  }, // body turn left
  {   70, 110, 110,  70, 110, 110, 110, 110,  500  }, // body turn right
  {   70,  70,  70,  70, 110,  70,  70, 110,  500  }, // body turn left
  {   70, 110, 110,  70, 110, 110, 110, 110,  500  }, // body turn right
  {   70,  90,  90,  70, 110,  90,  90, 110,  500  }  // leg1, 2 up ; leg3, 4 down
};
  execute_progmem(servo_matrix_fighting,steps);  
  }

void Q::push_up(){
  int steps = 11;
  const static int servo_matrix_push_up[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  90,  90, 110, 110,  90,  90,  70,  500  }, // start
  {  100,  90,  90,  80,  80,  90,  90, 100,  600  }, // down
  {   70,  90,  90, 110, 110,  90,  90,  70,  700  }, // up
  {  100,  90,  90,  80,  80,  90,  90, 100,  800  }, // down
  {   70,  90,  90, 110, 110,  90,  90,  70,  900  }, // up
  {  100,  90,  90,  80,  80,  90,  90, 100, 1500  }, // down
  {   70,  90,  90, 110, 110,  90,  90,  70, 2000  }, // up
  {  135,  90,  90,  45,  45,  90,  90, 135,  200  }, // fast down
  {   70,  90,  90,  45,  60,  90,  90, 135,  800  }, // leg1 up
  {   70,  90,  90,  45, 110,  90,  90, 135,  800  }, // leg2 up
  {   70,  90,  90, 110, 110,  90,  90,  70,  800  }  // leg3, leg4 up
};
  execute_progmem(servo_matrix_push_up,steps);  
  }

void Q::sleep(){
  int steps = 2;
  const static int servo_matrix_sleep[][SERVO_NUM+1] PROGMEM =  {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   30,  90,  90, 150, 150,  90,  90,  30,  500  }, // leg1,4 dn
  {   30,  45, 135, 150, 150, 135,  45,  30,  500  }, // protect myself
};
  execute_progmem(servo_matrix_sleep,steps);  
  }

void Q::dance1(){
  int steps = 10;
  const static int servo_matrix_dance1[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   90,  90,  90,  90,  90,  90,  90,  90,  400  }, // leg1,2,3,4 up
  {   50,  90,  90,  90,  90,  90,  90,  90,  400  }, // leg1 dn
  {   90,  90,  90, 130,  90,  90,  90,  90,  400  }, // leg1 up; leg2 dn
  {   90,  90,  90,  90,  90,  90,  90,  50,  400  }, // leg2 up; leg4 dn
  {   90,  90,  90,  90, 130,  90,  90,  90,  400  }, // leg4 up; leg3 dn
  {   50,  90,  90,  90,  90,  90,  90,  90,  400  }, // leg3 up; leg1 dn
  {   90,  90,  90, 130,  90,  90,  90,  90,  400  }, // leg1 up; leg2 dn
  {   90,  90,  90,  90,  90,  90,  90,  50,  400  }, // leg2 up; leg4 dn
  {   90,  90,  90,  90, 130,  90,  90,  90,  400  }, // leg4 up; leg3 dn
  {   90,  90,  90,  90,  90,  90,  90,  90,  400  }, // leg3 up
};
  execute_progmem(servo_matrix_dance1,steps);  
  }

void Q::dance2(){
  int steps = 9;
  const static int servo_matrix_dance2[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  45, 135, 110, 110, 135,  45,  70,  400  }, // leg1,2,3,4 two sides
  {  115,  45, 135,  65, 110, 135,  45,  70,  400  }, // leg1,2 up
  {   70,  45, 135, 110,  65, 135,  45, 115,  400  }, // leg1,2 dn; leg3,4 up
  {  115,  45, 135,  65, 110, 135,  45,  70,  400  }, // leg3,4 dn; leg1,2 up
  {   70,  45, 135, 110,  65, 135,  45, 115,  400  }, // leg1,2 dn; leg3,4 up
  {  115,  45, 135,  65, 110, 135,  45,  70,  400  }, // leg3,4 dn; leg1,2 up
  {   70,  45, 135, 110,  65, 135,  45, 115,  400  }, // leg1,2 dn; leg3,4 up
  {  115,  45, 135,  65, 110, 135,  45,  70,  400  }, // leg3,4 dn; leg1,2 up
  {   75,  45, 135, 105, 110, 135,  45,  70,  400  }, // leg1,2 dn
};
  execute_progmem(servo_matrix_dance2,steps);  
  }
void Q::dance3(){
  int steps = 10;
  const static int servo_matrix_dance3[][SERVO_NUM+1] PROGMEM = {
  // G14, G12, G13, G15, G16,  G5,  G4,  G2,  ms
  {   70,  45,  45, 110, 110, 135, 135,  70,  400  }, // leg1,2,3,4 bk
  {  110,  45,  45,  60,  70, 135, 135,  70,  400  }, // leg1,2,3 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  400  }, // leg1,2,3 dn
  {  110,  45,  45, 110,  70, 135, 135, 120,  400  }, // leg1,3,4 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  400  }, // leg1,3,4 dn
  {  110,  45,  45,  60,  70, 135, 135,  70,  400  }, // leg1,2,3 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  400  }, // leg1,2,3 dn
  {  110,  45,  45, 110,  70, 135, 135, 120,  400  }, // leg1,3,4 up
  {   70,  45,  45, 110, 110, 135, 135,  70,  400  }, // leg1,3,4 dn
  {   70,  90,  90, 110, 110,  90,  90,  70,  400  }, // standby
};
  execute_progmem(servo_matrix_dance3,steps);  
  }



Q myQ;

void setup(){
  Serial.begin(9600);
  Serial.println("Q begin~");
  int pins[SERVO_NUM] = {2,3,4,5,6,7,8,9};
  myQ.init(pins);
//  myQ.home();
//  myQ.zero();
  myQ.forward();
  myQ.backward();
  myQ.left_shift();
  myQ.right_shift();
  myQ.servo_zero();
  myQ.start();
  myQ.standby();
  myQ.turn_left();
  myQ.turn_right();
  myQ.lie();
  myQ.say_hi();
  myQ.fighting();
  myQ.push_up();
  myQ.sleep();
  myQ.dance1();
  myQ.dance2();
  myQ.dance3();
  myQ.standby();
  
  }

void loop(){
  
  }
