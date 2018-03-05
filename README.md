# Closed_loop_triholonomic
INTRODUCTION

The problem statement demanded for the construction of a Manual Robot whose main job is to transfer the shuttlecocks to the Automatic Robot for throwing from various throwing zones The manual bot is to be controlled by a team member. 

BASIC OPERTAION

We designed a tri-holonomic drive for the mobilty of the bot. The drive is being controlled using an XBOX 360 controller via Bluetooth modem(wireless SPI communication). The bot is  able to translate in any direction in the X-Y plane of the manual robot area and is also able to rotate about its own axis in both clockwise and counter-clockwise direction. Three Omni wheels oriented at 120 degrees to the adjacent wheels are used to achieve the required the degree of freedom. Three increamental rotary encoders were attached to each of the three motors for application of closed loop(PID control). A piston was mounted on the drive which lifts the rack of shuttlecocks for transfer. The piston is operated using pneumatics(using compressed air as fluid).


   COMPONENTS

Paper-phenolic sheet is used for the base of the final structure. Plywood had been used for prototype. Other components:

Arduino Mega
USB host shield
24V Lipo
9V Lipo
Three Omni wheels
Three Nylon-6 couplers
     Three Bane-Bot motors with  Planetary Gearbox
     Three Hercules 6V-36V, 16Amp Motor Driver
     Three Incremental Rotary Encoders
     XBOX 360 controller
     Bluetooth modem 
     Voltage regulators
     Piston
    Pneumatics arrangemnt
    Jumpers/cables



ALGORITHMS USED

 XBOXREVC header file has been used to receive input from the controller via the USB host shield.The formula used to control the velocity of individual motors for the input received from the controller is-  
rpm_giv1= (-0.667*x)+(0 * y)+(0.333*angle);
rpm_giv2= (0.333*x)+(-0.577 * y)+(0.333*angle);
rpm_giv3= (0.333*x)+(0.577 * y)+(0.333*angle);

where x is acceleration along x-axis, y is acceleration along y-axis and angle is the angular velocity about the axis of the bot. These formulas have been computed using inverse matrix calculation. Then the values have been mapped suitably within the pwm range.

The closed loop is executed with the help of the encoders which calculate the rpm of the motors using the TIMER header file and then implements the PID( PD in this case) . Kp and Kd were experimentally determined and have been tuned to the maximum extent for minimum error.

error1=rpm_giv1-rpm1; 
pwm1=pwm1 + (Kp*error1)+(Kd*((error1-prev_error1)/(t1-t2)));
 prev_error1=error1;
rpm_giv_prev1=rpm_giv1;


The drive moves with apparently zero drift which indicates that the closed loop has been applied successfully. It is also capable of turning with zero radius in both the directions. The left joystick of the controller controls the translation while the right one controls the rotation about its own axis.
