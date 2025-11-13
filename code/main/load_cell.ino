#define ADC2N 1.0f
#define N2Nm 1.0f

//Pin to read the load cell
#define LOADCELL_ANALOGPIN A3
 // N samples to correct the offset of the load cell
#define NSAMPLES_OFFSET_CORRECTION 1000

// Global variable to store the offset corrected of the load cell
float offset_load_cell = 0.0;


/*
 * Function: ReadLoadCell
 *  Function to read the channel associated to the connection with the load cell
 *  
 * Inputs: void
 *  
 * Outputs:
 *  -(float): Value given by the load cell in Nm.
 */
float ReadLoadCell(){
   return -(analogRead(LOADCELL_ANALOGPIN)-offset_load_cell)*ADC2N*N2Nm;
}

/*
 * Function: CorrectOffsetLoadCell
 *  Function to correct the offset of the load cell. The value is stored in 
 *  offset_load_cell
 *  
 * Inputs: void
 *  
 * Outputs: void
 */
void CorrectOffsetLoadCell(void){
  // Create a float variable to store the acumulated sum of values
  float cum_data_load_cell = 0.0;
  
  // Create a for loop to read NSAMPLES_OFFSET_CORRECTION samples and store it in the previous variable you have created.
  // Wait 1 milisecond between readings
  for (int i = 0;i<NSAMPLES_OFFSET_CORRECTION;i++){
   cum_data_load_cell = analogRead(LOADCELL_ANALOGPIN) + cum_data_load_cell;
   delay(1);
  }
  // Divide the accumulated sum per the number of samples you have taken and store it in offset_load_cell.
  offset_load_cell = cum_data_load_cell/NSAMPLES_OFFSET_CORRECTION;

  //Print a message to inform the user that the process of calibration has finished.
  Serial.println("The Offset of the Load Cell is Corrected!");
  Serial.println("The Offset of the Load Cell is: " + String(offset_load_cell));
 
}
