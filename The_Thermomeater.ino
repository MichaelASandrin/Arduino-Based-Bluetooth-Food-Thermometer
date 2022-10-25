/**The Thermomeater
 * 
 * A smart Food Thermometer than connects to your smart device
 * 
 * Created and Developed by: Michael Sandrin 2021
 * Course: EECS 2032
 * Instructor: Ebarhim Ghafar-Zadeh
 */

//Variables
int temp_Value = 0;
int reqTemp = 0;
boolean menuExit = false;
boolean optionExit = false;
boolean foodChoiceExit = false;
boolean readingExit = false;
int milliseconds = 0;
int mainMenuChoice = 0;
String foodName = "No Name";

//Setup ********************************************
void setup() {

// Speaker Audio Signal
#define audio_Pin 3

//Analog Temperature Signal
#define temp_Sensor A0

//User-Interface Buttons
#define BUTTON_LEFT 35
#define BUTTON_CENTER 33
#define BUTTON_RIGHT 31

//Start of the Serial for the Bluetooth Module
Serial1.begin(9600);
delay(500);
menuExit = false;

//Setting Pin Modes
pinMode(audio_Pin, OUTPUT);
pinMode(temp_Sensor, INPUT);
pinMode(BUTTON_LEFT, INPUT);
pinMode(BUTTON_CENTER, INPUT);
pinMode(BUTTON_RIGHT, INPUT);


// Plays Start Up Sound and Tells User "Connection Successful!"
sounds(2);
Serial1.println("Device Connected");
Serial1.println("");
delay(3000);
sounds(8);
Serial1.println("Sensor Detected");
Serial1.println("");
delay(3000);

}

//Start of the Loop ********************************
void loop() {

//Loop Variables
int liveTemp = 0;
int cookedCounter = 0;
boolean cookedExit = false;
boolean cooked = false;

//First Loop for the Main Menu
  while(menuExit != true){

    //Runs the Main Menu Method
    mainMenu();
    delay(100);

    
  //Button Choice for Main Menu
  do{
   
  //Left Button Choice
  if(digitalRead(BUTTON_LEFT) == HIGH ){

   //Option Select Sound
   sounds(0);
   //Selects the First Choice
   mainMenuChoice = 1;
   //Exits the Option Selection Loop
   optionExit = true;
  }

  //Center Button Choice
  else if(digitalRead(BUTTON_CENTER) == HIGH ){
   
   //Option Select Sound
   sounds(0);
   //Selects the Second Choice
   mainMenuChoice = 2;
   //Exits the Option Selection Loop
   optionExit = true;
  }

  //Right Button Choice
   else if(digitalRead(BUTTON_RIGHT) == HIGH ){
    
    //Option Select Sound
    sounds(0);
    //Selects the Third Choice
    mainMenuChoice = 3;
    //Exits the Option Selection Loop
    optionExit = true;
    //Exits the Main Menu
    menuExit = true;
  }
  
  delay(150);

  //While Statement for the Button Choice
  }while(optionExit != true);

  //Resets the Option Selection
  optionExit = false;

  //The Main Menu Choice 
  if((mainMenuChoice > 0)&&(mainMenuChoice < 4)){
    
    
    // Food Timer Option   -----------------------------

  //If the Food Timer is chosen  
  if(mainMenuChoice == 1){

  //Food Timer Variables
  boolean timerExit = false;
  int minuteIncrement = 2;

        //Prints the Intial Time Set by Program
        Serial1.print("Initial Time: ");
        Serial1.print(minuteIncrement);
        Serial1.print(" Mins");
        Serial1.print(" ------------------");

    //Calls on Timer Button Map for User Interface    
    timerButtonMap();

//Do-While Loop for the Button Choice
do{
   
  //Left Button Choice
  if(digitalRead(BUTTON_LEFT) == HIGH ){

    //Option Select Sound
   sounds(0);

   if(minuteIncrement > 2){
    
   //Lowers the Time by 1 Minute
   minuteIncrement -= 1;

        //Prints the current time for the user
        Serial1.print("Time: ");
        Serial1.print(minuteIncrement);
        Serial1.println(" Mins");

        
   }else{
    //Plays Error Sound
    sounds(1);
    
    //Displays Error
    Serial1.println("Too Little Time!");
    Serial1.println("Must Add Time!");
    
   }
  }

  //Center Button Choice
  else if(digitalRead(BUTTON_CENTER) == HIGH ){
   
   //Option Select Sound
   sounds(0);

        //Displays Chosen Time by User
        Serial1.println("Timer is Set For: ");
        Serial1.print(minuteIncrement);
        Serial1.println(" Mins");

        delay(2000);

      //Calls on Millisecond Conversion Function

      milliseconds =  minsToMillisec(minuteIncrement);
      
   //Exits the Option Selection Loop
   timerExit = true;
  }

  //Right Button Choice
   else if(digitalRead(BUTTON_RIGHT) == HIGH ){
    
    //Option Select Sound
    sounds(0);
    
     if(minuteIncrement < 720){
      
   //Lowers the Time by 1 Minute
   minuteIncrement += 1;

        //Prints the current time for the user
        Serial1.print("Time: ");
        Serial1.print(minuteIncrement);
        Serial1.println(" Mins");

        
   }else{
    
    //Plays Error Sound
    sounds(1);
    
    //Displays Error
    
    Serial1.print("Not Possible!");
    Serial1.print("Must Add Time!");
   }
  }

  //Set the value to true so the Menu can be exited
  menuExit = true;
    
  delay(150);

 //Finishes the loop as the time has been confirmed by the user
 }while(timerExit != true);

  //Calls on the Food Timer Function for the user
  foodTimer(milliseconds);
  
  }
  
  //Food Thermometer Option -------------------------- 
  else if(mainMenuChoice == 2){

     //Calls the Food Menu for the User Interface
     foodMenu();
    delay(100);
    
  //Food Thermometer Menu Variables
  optionExit = false;
  foodChoiceExit = false;

  //Food Thermometer Do-While Loop
  do{

    //Button Choice Do-While Loop
    do{

   //Left Button Choice
  if(digitalRead(BUTTON_LEFT) == HIGH ){
    
    //Option Select Sound
    sounds(0);
    
    //Sets Values for Chicken
    foodName = "Chicken";
    reqTemp = 165;
    
    //Displays Chosen Option to User
    Serial1.println("Chicken (165°F)");
    
    //Tells Program that an Option has been Chosen
   optionExit = true;
   foodChoiceExit = true;
   
  }

   //Center Button Choice
  else if(digitalRead(BUTTON_CENTER) == HIGH ){
    
    //Option Select Sound
    sounds(0);
    
    //Sets Values for Beef
    foodName = "Beef";
    reqTemp = 145;
    
    //Displays Chosen Option to User
    Serial1.println("Beef (145°F)");
    
    //Tells Program that an Option has been Chosen
   optionExit = true;
   foodChoiceExit = true;
   
  }

   //Right Button Choice
   else if(digitalRead(BUTTON_RIGHT) == HIGH ){
    
    //Option Select Sound
    sounds(0);
    menuExit = false;
    reqTemp = 100;
    
      //Calls on Increment Button Map for the User Interface
      incremButtonMap();

        //Loop for the User to set Required Temperature
        do{

        
  //Left Button Choice
  if(digitalRead(BUTTON_LEFT) == HIGH ){

   //Option Select Sound
   sounds(0);

  //If the temperature is greater than the min temperature (0°F)
   if(reqTemp > 0){
    
   //Lowers the Temperature by 5 Degrees
   reqTemp -= 5;

        //Prints the current temperature for the user
        Serial1.print("Current Temp: ");
        Serial1.print(reqTemp);
        Serial1.println("°F");
        
   }else{
    
    //Plays Error Sound
    sounds(1);
    
    //Displays Error
    Serial1.print("Temp Too Low ");
    Serial1.print("Cannot Go Lower \n");
    
   }
  }

  //Center Button Choice
  else if(digitalRead(BUTTON_CENTER) == HIGH ){
   
   //Option Select Sound
   sounds(0);
   
   //Exits the Option Selection Loop
    menuExit = true;
  }

  //Right Button Choice
   else if(digitalRead(BUTTON_RIGHT) == HIGH ){
    
   //Option Select Sound
   sounds(0);

    //If the temperature is lower than the max temperature (390°F)
   if(reqTemp < 390){
    
   //Raises the Temperature by 5 Degrees
   reqTemp += 5;

   //Prints the current temperature for the user
        Serial1.print("Current Temp: ");
        Serial1.print(reqTemp);
        Serial1.println("°F");

   }else{
    
    //Plays Error Sound
    sounds(1);
    
    //Displays Error
    Serial1.println("Temp Too High ");
    Serial1.println("Cannot Go Higher");
    
   }
  }
  
  delay(150);

    //Finishes the loop as the temperature has been confirmed by the user
    }while(menuExit != true);
    
        //Tells Program that an Option has been Chosen
        Serial1.print("Required Temp:");
        Serial1.print(reqTemp);
        Serial1.println("°F");
    
    //Sets Values for the Food
    foodName = "Food";

    //Sets new values for the Variables
    menuExit = false;
    optionExit = true;
    foodChoiceExit = true;
   }

  //Finishes the loop as the food has been confirmed by the user
  }while(foodChoiceExit != true);
   foodChoiceExit = false;
   
   // Live Temp Reading

    delay(2000);

    //Tells the User that the Temperature is now being read
  Serial1.print("Now Reading Temp");
    delay(2000);

    //Do-While Loop for Temperature Reading
    int y = 0;
    do{
      
    //Sets the value of the Live Temperature Reading with the function call
    liveTemp = liveTempReading();
      delay(1000);
      
   //If the Temperature being read is greater than or equal to what is required
   if(liveTemp >= reqTemp){

    //Do-While Loop to see if the next 20 Live Temperature Readings are also
    //greater than or equal to what is required
    do{

      //Sets the value of the Live Temperature Reading with the function call
      liveTemp = liveTempReading();
        delay(1000);

      //If the last 20 Temperature readings are less than the required temperature
      if(cookedCounter < 20){

      //If the Temperature being read is greater than or equal to what is required
      if(liveTemp >= reqTemp){

        //Increment the number of readings that exceed or equal the required temperature
        cookedCounter++;

        //If the number of good readings is 15
        if(cookedCounter == 15){

          sounds(10);
        }

       //If the Live Temperature Reading is less than the required temperature
      }else{

       //Reset the values of the variables used
        cookedCounter = 0;
        cookedExit = true;
      }

      //If the last 20 Live Temperature Readings prove the food is cooked
    }else if(cookedCounter >= 20){

      //Changes the values of the variables used
      cookedExit = true;
      readingExit = true;
      
    }

      //Finishes the loop as the food has been cooked
      }while(cookedExit != true);
   }

   //Finishes the loop as the food has been cooked and no reading is needed
   }while(readingExit != true);
   
   sounds(11);

   //Resets Variables if it needs to happen again
   cookedCounter = 0;
   cookedExit = false;
   readingExit = false;


    //Prints that the food is cooked on the User Interface
    Serial1.print("------------------\n");
    Serial1.print(" The ");
    Serial1.print(foodName);
    Serial1.print(" is cooked\n");
    Serial1.print("-----------------\n");

    //Sets the value to exit the loop
    optionExit = true;

  delay(1500);
  
  //Finishes the loop as the food has been cooked
  }while(optionExit != true);

  //Resets Variables if it needs to happen again
  optionExit = false;

    // Turning Off Option         ----------------------
    
    //The User chooses to turn off the Thermomeater
  }else if(mainMenuChoice == 3){
  
     //Calls on the Turning Off Function to print the User Interface  
     turningOff();

     //Creates an Infinite Loop so the user must reset the Arduino
     //Board to start the system from the beginning
     while(0 != 1){
    delay(100000);
   }
   
  }

  //Resets the Main Menu Choice if the menu appears again
  mainMenuChoice = 0;
}


//Asks User if they want the Device Kept On
Serial1.println(" Keep Device On? ");
Serial1.println(" L: Yes | R: No ");
Serial1.println(" -------------- ");

//Do-While Loop to Take Button Input to Keep System On
do{

  //Left Button Choice
  if(digitalRead(BUTTON_LEFT) == HIGH ){
    
    //Option Select Sound
    sounds(0);

   //Sets Variable to Exit the Button Choice
   optionExit = true;

   //Displays that the program is restarting on User Interface
   Serial1.print("Now Restarting...\n");
   delay(3000);

   //Sets Variable to Enter the Menu Once Again
   menuExit = false;
  }

  //Center Button Choice
  
  else if(digitalRead(BUTTON_CENTER) == HIGH ){
    
    //Option Select Sound
    sounds(0);

    //Prints that the Users Choice is Invalid
    Serial1.print("Left or Right Only\n");
  }

   //Right Button Choice
   else if(digitalRead(BUTTON_RIGHT) == HIGH ){
    
    //Option Select Sound
    sounds(0);

   //Sets Variable to Exit the Button Choice and Enter the Menu Once Again
   optionExit = true;
   menuExit = true;
   
   delay(1000);

   //Calls on the Turning Off Function to print the User Interface  
   turningOff();

   //Creates an Infinite Loop so the user must reset the Arduino
   //Board to start the system from the beginning
   while(0 != 1){
    delay(100000);
   }
   
   }

//Finishes as the user has chosen to reset the system/program
}while(optionExit!=true);

//Resets the Variable to be used again
optionExit = false;

//End of Loop **************************************

}

//Resets the Variables to be used again
menuExit = false;
optionExit = false;
}


//Main Menu Display ********************************
void mainMenu(){

  //Prints out the Main Menu for the User Interface
  Serial1.write("     Main Menu        ------------------");
  delay(250);
  Serial1.write("  | 1. Timer        ");
  delay(250);
  Serial1.write("  | 2. Food & Meat  ");
  delay(250);
  Serial1.write("  | 3. Turn Off       ------------------");
  delay(250);
}

//Food Menu ****************************************
void foodMenu(){

    //Prints out the Food Menu for the User Interface
  Serial1.write("    Preset Food       ------------------");
  delay(450);
  Serial1.write("  | 1. Chicken      ");
  delay(450);
  Serial1.write("  | 2. Beef         ");
  delay(450);
  Serial1.write("  | 3. Other Foods    ------------------");
  delay(450);
}

//Increment Button Map *****************************
void incremButtonMap(){

  //Prints out the Increment Button Map for the User Interface
  Serial1.print("   Temp Increment   ");
  delay(250);
  Serial1.print(" [LEFT|CENTER|RIGHT]");
  delay(250);
  Serial1.print(" [ -5 |DONE| +5 ]   ------------------\n");
  delay(250);
}

//Timer Button Map *********************************
void timerButtonMap(){

  //Prints out the Timer Button Map for the User Interface
  Serial1.print("   Timer Increment   ");
  delay(250);
  Serial1.print(" [LEFT|CENTER|RIGHT]");
  delay(250);
  Serial1.print(" [ -1 |DONE| +1 ]   ------------------\n");
  delay(250);
}

//Turning Off Function *****************************
void turningOff(){

  //Prints out the Turning for the User Interface
  Serial1.write("Turning Off...");
    delay(1000);

   //For Loop to Space the Previous Text away from the Screen
   for(int i = 0; i <20;i++){
    Serial1.write("  \n");
    delay(10);
   }
   
   sounds(3);

   //Prints out my name and year as Credits
   Serial1.write("Michael Sandrin 2021");
}

//Minutes to Milliseconds Calculation for Delays ***
int minsToMillisec(int mins){

  //Calculation To convert Mins to Milliseconds
  int millisec = mins * 60 * 1000; 

  //Returns the Millisecond Value
  return(millisec);
}

//Milliseconds to Minutes Calculation for Delays ***
double millisecToMins(int millisec){

  //Calculation To convert Milliseconds to Mins
  double mins = (((double)millisec) / 1000.00) / 60.00; 

  //Returns the Minutes Value
  return(mins);
}

// Food Timer Function *****************************
void foodTimer(int milliseconds){

  //Calculates the Time of the First Half of the Timer
  double timerFirstHalf = milliseconds / 2.00;

  //Calculates the Time of the Second Half of the Timer
  //Not Including the Last Minute and Delays
  double timerSecondHalf = timerFirstHalf - 63200.00;

  //Sets the Time that would be Displayed in the User Interface
  double displayTime = 0.0;

  //Displays the Timer has Begun on the User Interface
  Serial1.println("Timer has Begun!");
  sounds(4);

  //Delays Based on the First Half of the Timer
  delay((int)timerFirstHalf);

  //Changes the display time to be printed out
  displayTime = (millisecToMins(milliseconds)) - (millisecToMins(timerFirstHalf));

  //Prints out the Timer being Halfway and the Remaining 
  //Time on the User Interface
  Serial1.print("Timer is Halfway! \n");
  Serial1.print(" Time left: ");
  Serial1.print(displayTime);
  Serial1.println(" Mins");
  sounds(5);

  //Delays Based on the Second Half of the Timer
  delay((int)timerSecondHalf);

  //Prints that there is One Minute Left on the User Interface
  Serial1.println("One Minute Left!");
  sounds(6);

  //Delays the program for one minute (60000 Milliseconds)
  delay(60000);

  //Prints that the timer is done on the User Interface
  Serial1.println("Timer is Finished!");
  sounds(7);
}

// Converts the Analog Value to Fahrenheit *********
double tempConversion(int tempReading){
  double realTemp = (100 + ((double)tempReading)/50 + 3);
  return(realTemp);
}

// Live Temperature Reading Function ***************
int liveTempReading(){

  // Takes Analog Signal from the Temperature Probe
  int tempReading = analogRead(temp_Sensor);

  //Converts the Analog Signal to the Temperature
  double realTemp = tempConversion(tempReading);

    //Prints the Live Temp to the User Interface
    Serial1.write("Live Temp: ");
    Serial1.print(realTemp);
    Serial1.write("°F \n");

    //Returns the Temperature to where it was called
    return(realTemp);
   
}

// Sounds Function *********************************
void sounds(int song_Choice){
  
//Option Select Sound
if(song_Choice == 0){
analogWrite(audio_Pin, 50);
delay(50);
analogWrite(audio_Pin, 0);
delay(50);
analogWrite(audio_Pin, 50);
delay(50);
analogWrite(audio_Pin, 0);
}

//Error Sound 
else if(song_Choice == 1){
analogWrite(audio_Pin, 80);
delay(1000);
analogWrite(audio_Pin, 5);
delay(1000);
analogWrite(audio_Pin, 80);
delay(1000);
analogWrite(audio_Pin, 5);
delay(1000);
analogWrite(audio_Pin, 80);
delay(1000);
analogWrite(audio_Pin, 5);
delay(1000);
analogWrite(audio_Pin, 0);
}

//Start Up Song
 else if(song_Choice == 2){
analogWrite(audio_Pin, 1);
delay(100);
analogWrite(audio_Pin, 5);
delay(100);
analogWrite(audio_Pin, 10);
delay(100);
analogWrite(audio_Pin, 15);
delay(100);
analogWrite(audio_Pin, 20);
delay(100);
analogWrite(audio_Pin, 25);
delay(100);
analogWrite(audio_Pin, 30);
delay(100);
analogWrite(audio_Pin, 35);
delay(100);
analogWrite(audio_Pin, 40);
delay(100);
analogWrite(audio_Pin, 45);
delay(100);
analogWrite(audio_Pin, 50);
delay(100);
analogWrite(audio_Pin, 0);
delay(1500);
analogWrite(audio_Pin, 50);
delay(50);
analogWrite(audio_Pin, 0);
delay(50);
analogWrite(audio_Pin, 50);
delay(50);
analogWrite(audio_Pin, 0);
}

//Shut Down Song
else if(song_Choice == 3){
analogWrite(audio_Pin, 50);
delay(50);
analogWrite(audio_Pin, 0);
delay(50);
analogWrite(audio_Pin, 50);
delay(50);
analogWrite(audio_Pin, 0);
delay(800);
analogWrite(audio_Pin, 50);
delay(100);
analogWrite(audio_Pin, 45);
delay(100);
analogWrite(audio_Pin, 40);
delay(100);
analogWrite(audio_Pin, 35);
delay(100);
analogWrite(audio_Pin, 30);
delay(100);
analogWrite(audio_Pin, 25);
delay(100);
analogWrite(audio_Pin, 20);
delay(100);
analogWrite(audio_Pin, 15);
delay(100);
analogWrite(audio_Pin, 10);
delay(100);
analogWrite(audio_Pin, 5);
delay(100);
analogWrite(audio_Pin, 1);
delay(100);
analogWrite(audio_Pin, 0);
}

//Timer Start
else if(song_Choice == 4){
analogWrite(audio_Pin, 65);
delay(250);
analogWrite(audio_Pin, 0);
delay(750);
analogWrite(audio_Pin, 65);
delay(250);
analogWrite(audio_Pin, 0);
delay(750);
analogWrite(audio_Pin, 65);
delay(250);
analogWrite(audio_Pin, 0);
delay(750);
analogWrite(audio_Pin, 40);
delay(700);
analogWrite(audio_Pin, 0);
}

//Timer Halfway
else if(song_Choice == 5){
analogWrite(audio_Pin, 5);
delay(350);
analogWrite(audio_Pin, 25);
delay(350);
analogWrite(audio_Pin, 45);
delay(350);
analogWrite(audio_Pin, 65);
delay(1000);
analogWrite(audio_Pin, 0);
}

//Timer Last Minute
else if(song_Choice == 6){
analogWrite(audio_Pin, 25);
delay(150);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(150);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(700);
analogWrite(audio_Pin, 0);
}

//Timer Finish
else if(song_Choice == 7){
analogWrite(audio_Pin, 25);
delay(250);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(250);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(250);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(250);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(250);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(250);
analogWrite(audio_Pin, 0);
delay(150);
analogWrite(audio_Pin, 25);
delay(800);
analogWrite(audio_Pin, 0);
delay(1500);
}

//Temperature Detected
else if(song_Choice == 8){
analogWrite(audio_Pin, 65);
delay(150);
analogWrite(audio_Pin, 5);
delay(150);
analogWrite(audio_Pin, 0);
delay(1000);
analogWrite(audio_Pin, 65);
delay(150);
analogWrite(audio_Pin, 5);
delay(150);
analogWrite(audio_Pin, 0);
}

//Food is Chosen
else if(song_Choice == 9){
analogWrite(audio_Pin, 65);
delay(50);
analogWrite(audio_Pin, 5);
delay(60);
analogWrite(audio_Pin, 65);
delay(1000);
analogWrite(audio_Pin, 0);
}

//Food is Almost Done
else if(song_Choice == 10){
analogWrite(audio_Pin, 65);
delay(150);
analogWrite(audio_Pin, 5);
delay(150);
analogWrite(audio_Pin, 0);
delay(400);
analogWrite(audio_Pin, 65);
delay(150);
analogWrite(audio_Pin, 5);
delay(150);
analogWrite(audio_Pin, 0);
delay(400);
analogWrite(audio_Pin, 65);
delay(150);
analogWrite(audio_Pin, 5);
delay(700);
analogWrite(audio_Pin, 0);
}


//Food is Cooked
else if(song_Choice == 11){
analogWrite(audio_Pin, 8);
delay(200);
analogWrite(audio_Pin, 40);
delay(400);
analogWrite(audio_Pin, 8);
delay(200);
analogWrite(audio_Pin, 40);
delay(400);
analogWrite(audio_Pin, 8);
delay(200);
analogWrite(audio_Pin, 135);
delay(1500);
analogWrite(audio_Pin, 0);

}
}
