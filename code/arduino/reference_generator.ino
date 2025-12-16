#define DEG2RAD 0.01745 //2pi/360
#define RAD2DEG 57.29577 //360/2pi

//Admittance model
float desired_position = 0.0;
float desired_velocity = 0.0;
float desired_acceleration = 0.0;
// Model parameters
float virtual_inertia  = 0;   // J
float virtual_damping  = 0;    // B
float virtual_stiffness = 0;   // K

float resting_pos = 45; //deg
float resting_vel = 0; //deg/s

// Safety limits (modify as needed)
float vel_max = 200.0;



/*
 * Function: ReferenceGenerator
 *  Generates a reference torque value following an admittance model, compesating inertia and gravity if desired.
 *    
 * Inputs: 
 *  - time_diff (float): Current time stamp of the system in seconds.
 *  - interaction_torque (int): Value of the load cell measured by the ADC.
 *  
 * Outputs:
 *  - (float): Desired position in degrees.
 */
float ReferenceGenerator(float time_diff, float interaction_torque){
  // ---- 1) Compute acceleration (Eq.1 rearranged) ----
    desired_acceleration = (interaction_torque - virtual_damping * desired_velocity - virtual_stiffness * (desired_position - resting_pos)* DEG2RAD) / virtual_inertia;

    // ---- 2) Integrate acceleration -> velocity ----
    desired_velocity += desired_acceleration * time_diff;

    // ---- 3) Integrate velocity -> position ----
    desired_position += RAD2DEG*desired_velocity * time_diff;

    // ---- 4) Reset if limits exceeded ----
    if(desired_position > MAXPOSLIMIT)
    {
        desired_position = MAXPOSLIMIT;
        desired_velocity = 0;
    }
    else if (desired_position < MINPOSLIMIT){
        desired_position = MINPOSLIMIT;
        desired_velocity = 0;
    }

    // Return desired reference position in degrees
    return desired_position;
}

 
