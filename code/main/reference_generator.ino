#define DEG2RAD 0.01745 //2pi/360
#define RAD2DEG 57.29577 //360/2pi

//Admittance model
float desired_position = 0.0;
float desired_velocity = 0.0;
float desired_acceleration = 0.0;
float virtual_inertia = 0.0;
float virtual_damping = 0.0;
float virtual_stiffness = 0.0;
float resting_pos = 45; //deg
float resting_vel = 0; //deg/s

// Define position limits (Example values, adjust as needed for the device)
#define MAX_POSITION_RAD (90.0 * DEG2RAD) 
#define MIN_POSITION_RAD (0.0 * DEG2RAD)

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
  
  // Convert resting position to radians for calculation
  float resting_pos_rad = resting_pos * DEG2RAD;

  // F = J*q̈ + B*q̇ + K*Δq --> q̈ = (F - B*q̇ - K*Δq) / J
  float restoring_force = (virtual_damping * desired_velocity) + (virtual_stiffness * (desired_position - resting_pos_rad));
                          
  if (virtual_inertia != 0.0) {
      desired_acceleration = (interaction_torque - restoring_force) / virtual_inertia;
  } else {
      // Handle division by zero or use a very large value to simulate infinite inertia
      desired_acceleration = 0.0; 
  }

  // Euler Integration: Velocity (q̇_k = q̇_{k-1} + q̈_k * Δt)
  desired_velocity = desired_velocity + desired_acceleration * time_diff;
  
  // Euler Integration: Position (q_k = q_{k-1} + q̇_k * Δt)
  desired_position = desired_position + desired_velocity * time_diff;
  
  // Apply limits and reset state (as per Exercise 3.1 )
  if (desired_position > MAX_POSITION_RAD || desired_position < MIN_POSITION_RAD) {
      // Reset position to the limit and set velocity/acceleration to zero
      if (desired_position > MAX_POSITION_RAD) {
          desired_position = MAX_POSITION_RAD;
      } else {
          desired_position = MIN_POSITION_RAD;
      }
      
      // Reset velocity and acceleration
      desired_velocity = resting_vel * DEG2RAD; // Reset velocity to the resting state (0 rad/s)
      desired_acceleration = 0.0;
  }
  
  // Return the desired position in degrees
  return desired_position * RAD2DEG;
}
 
