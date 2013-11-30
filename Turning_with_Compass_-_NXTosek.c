/* nxtgt.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(TaskInitialize);
DeclareTask(TaskSonar);

/* Definitions */
#define MOTOR_LEFT         NXT_PORT_B
#define MOTOR_RIGHT        NXT_PORT_C

void ecrobot_device_initialize()
{
	ecrobot_init_compass_sensor(NXT_PORT_S1);
	ecrobot_init_bt_connection();
}

void ecrobot_device_terminate()
{
	ecrobot_term_compass_sensor(NXT_PORT_S1);
	nxt_motor_set_speed(MOTOR_RIGHT, 0, 1);
	nxt_motor_set_speed(MOTOR_LEFT, 0, 1);	
	ecrobot_term_bt_connection();
}

void user_1ms_isr_type2(void)
{
	StatusType ercd;	

	ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
	if(ercd != E_OK)
  	{
    	ShutdownOS(ercd);
  	}
}

/* TaskGyro */
TASK(TaskMotor)
{
	systick_wait_ms(2000);	
	int degrees = 90;
	
	int goal = (ecrobot_get_compass_sensor(NXT_PORT_S1) + degrees) % 360;
	
	while(ecrobot_get_compass_sensor(NXT_PORT_S1) != goal)
	{
		ecrobot_set_motor_speed(MOTOR_RIGHT, -15);	// set motorB to speed -15
		ecrobot_set_motor_speed(MOTOR_LEFT, 15);    // set motorC to speed 15
	}
	ecrobot_set_motor_speed(MOTOR_RIGHT, 0);	// set motorB to speed 0
    ecrobot_set_motor_speed(MOTOR_LEFT, 0);    // set motorC to speed 0
}
