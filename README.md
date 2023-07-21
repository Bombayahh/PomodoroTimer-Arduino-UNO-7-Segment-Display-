# PomodoroTimer-Arduino-UNO-7-Segment-Display-
1. A simple pomodoro timer created with 7 segments display. Written with support of SevSeg library.
2. Written in state machine style to practice with it, a push button is used to interrupt and change state.

   i.  Setup phase : Allow user to adjust resistance and choose required countdown minutes. Press push button after done setting timer.

   ii. Running Phase: Start counting down based on minutes set. Green LED light up. If user click push button at this phase, the timer will be reset and rerun agian.

   iii. Finish State: Timer stop at 0 seconds. Red LED light up. Press push button can go back setup phase.

Connections:

   1. Pin 2 Arduino UNO as interrupt pin => push button => 1k ohm resistor => ground
   
   2. Pin A0 Arduino UNO => red LED => 1k ohm resistor => ground
   
   3. Pin A1 Arduino UNO => green LED => 1k ohm resistor => ground
   
   4. Pin A3 Arduino UNO => variable resistor center pin (5V to left pin and ground to right pin of the variable resistor)

   5. 7 Segment Display Common Anode in my case:
   
        Top 6 pins (from left to right):
        
        1 => 1k ohm resistor => Pin 1 on arduino
        
        2 => Pin 6 on arduino
        
        3 => Pin 11 on arduino
        
        4 => 1k ohm resistor => Pin 3 on arduino
        
        5 => 1k ohm resistor => Pin 4 on arduino
        
        6 => Pin 7 on arduino
        
        Bottom 6 pins (from left to right):
        
        1 => Pin 10 on arduino
        
        2 => Pin 9 on arduino
        
        3 => Pin 13 on arduino
     
        4 => Pin 8 on arduino
        
        5 => Pin 12 on arduino
        
        6 => 1k ohm resistor => Pin 5 on arduino
