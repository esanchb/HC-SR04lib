//
//  HC_SR04_lib.h
//  SensorArch
//
//  Created by Eric on 23/04/16.
//  Copyright (c) 2016 Eric Sanchez B. All rights reserved.
//

#ifndef SensorArch_HC_SR04_lib_h
#define SensorArch_HC_SR04_lib_h


/**
 *
 * \enum    HC_STATES_ENUM
 *
 * \brief   Values that represent HC_STATES_ENUM. 
**/
typedef enum{
    HC_SR04_OFF=0,        ///< Sensor Hw Disabled 
    HC_SR04_TIMEOUT_READ, ///< Communication Error with the Hardware
    HC_SR04_READ_OK,	  ///< Valid Read from Ultrasonic Sensor
    HC_SR04_UNDER_MIN,    ///< The readed value is under the min threshold
    HC_SR04_OVER_MAX,     ///< The readed value is under the max threshold
    HC_SR04_READ_ERR      ///< Sensor Communication Error
}HC_STATES_ENUM;


/**
 *
 * \enum    System_unit
 *
 * \brief   Values that represent System_unit . 
**/
typedef enum{
    UNITS_METRIC=0,		///< Set measure conversion to Centimeters. 
    UNITS_ENGLISH		///< Set measure conversion to Inches.
}System_unit;


#define METRIC_SYSTEM_MIN_CM          (4.0f)	///< Metrics System Default Min Threshold
#define METRIC_SYSTEM_MAX_CM        (400.0f)	///< Metrics System Default Max Threshold

#define ENG_SYSTEM_MIN_INCH           (1.5f)	///< English System Default Min Threshold
#define ENG_SYSTEM_MAX_INCH         (157.4f)	///< English System Default Max Threshold

#define ERROR_VALUE                      (0)	///< Error Value
#define TIMEOUT_ERROR_VALUE              (0)	///< Timeout Const Error Value

#define UNITS_ENGLISH_DIV            (58.2f)	///< English const conversion
#define UNITS_METRIC_DIV            (148.0f)	///< Metrics const conversion

#define TRIG_OFF_MS                        2	///< Time HIGH in microseconds
#define TRIG_ON_MS                        10	///< Time LOW in microseconds


class HC_SR04Dev{
private:
    // Variables
    int Hc_sr04_trigger;
    int Hc_sr04_echo;
    unsigned long m_thmax;   // MaxThreshold
    unsigned long m_thmin;   // MinThreshold
    unsigned long Hc_sr04_Measure;
    unsigned long Hc_sr04_MeasureHw;
    unsigned char Hc_sr04_Status;
    System_unit Hc_sr04_units;
    
    // Methods
    virtual unsigned long HC_SR04_hw_Read();
    void HC_SR04_hw_Config();
    void HC_SR04_hw_Trigger() const;
    unsigned char MetricConv();
    unsigned char EngConv();
    
public:
	/**  
 	* @brief Class Constructor ::HC_SR04Dev
	* The class ::HC_SR04Dev it´s initialized with the main parameters _trigger_pin and _echo_pin and _units_conf.
	* @param [_trigger_pin] Trigger Arduino Pin
	* @param [_echo_pin] Echo Arduino Pin
	* @param [_units_conf] Configure Unit System for cm / inch , this input acepts ::UNITS_METRIC for metrics or  ::UNITS_ENGLISH for english
	*
	* @note Default Threshold Configuration for ::UNITS_METRIC
	*  MaxThreshold= ::METRIC_SYSTEM_MAX_CM ,
	*  MinThreshold= ::METRIC_SYSTEM_MIN_CM	
	*                                                           
	* @note Default Threshold Configuration for ::UNITS_ENGLISH..
	*  MaxThreshold= ::ENG_SYSTEM_MAX_INCH ,
	*  MinThreshold= ::ENG_SYSTEM_MIN_INCH	
	*
 	*/ 
    HC_SR04Dev(int _trigger_pin,int _echo_pin,System_unit _units_conf);

	/**  
 	* @brief Class Constructor ::HC_SR04Dev
	* The class ::HC_SR04Dev it´s initialized with the main parameters _trigger_pin and _echo_pin,
	* @note Default Configuration..
	*  When the units system is not specified , the units system are configured by default to ::UNITS_METRIC ,
	*  MaxThreshold= ::METRIC_SYSTEM_MAX_CM ,
	*  MinThreshold= ::METRIC_SYSTEM_MIN_CM	
	* @param [_trigger_pin] Trigger Arduino Pin
	* @param [_echo_pin] Echo Arduino Pin
 	*/ 
    HC_SR04Dev(int _trigger_pin,int _echo_pin);
   
	/**  
 	* @brief  Hardware Syncronization
 	*
 	* @return ::HC_STATES_ENUM Read Status
 	*/ 
    unsigned char Sync();
    
	/**  
 	* @brief  Returns the distance readed from the HC_SR04 Sensor in Centimeters or Inches
 	* @return [unsigned long] Returns the measure from the Sensor  in Centimeters or Inches ::System_unit
 	*/ 	
	unsigned long Read();

	/**  
 	* @brief  Returns the Status from the Last Read.
 	*
 	* @return ::HC_STATES_ENUM Read Status
 	*/ 
    unsigned char Status();

	/**  
 	* @brief Set Min and Max Threshold limits.
 	* @param [IN] Min value in cm or inches
	* @param [OUT] Max value in cm or inches
 	* @return void
 	*/ 
    void SetMinMax(unsigned long _min_range,unsigned long _max_range);
};

/**
* \mainpage The Sensor HC-SR04 Arduino Library v1.0  mainpage documentation
 *
 * \section intro_sec Overview
 *
 *  Sensor HC-SR04 Arduino Library v1.0 
 *
 * \section lib_fatures_sec Library Features

      > Error Handling
      > Unit Coversion Support (Centimeters <> Inches)
      > Multiple Arduino Board Support
      > Configurable Min Max Limits
      > Simple adquisition process
\image html http://oi64.tinypic.com/mt15w3.jpg "Hardware Configuration" width=10cm
 *
 * \subsection hwconfig_step Step 1: Hardware Configuration
    
    Select Arduino pin assigment:
    

    Sensor        Arduino Uno
     TriggerPin   12
     EchoPin      11
     VDD          Vcc 5v
     GND          Gnd

    Units System = Metrics (Centimeters)

    \code{.cpp}
    const int Triger_Pin = 12;
    const int Echo_Pin = 11;
    HC_SR04Dev Sensor_A(Triger_Pin, Echo_Pin,UNITS_METRIC);
    \endcode
    

 *
 * \subsection step1 Step 2: Arduino Setup 
  
  We can configure the max and min limits for the  HC_SR04 Library ....
  
  \code{.cpp}
   void setup() {
     Serial.begin(9600); // Set BaudRate
     // Set Max and Min thresholds
     // Min: 10 cm
     // Max:200 cm
     Sensor_A.SetMinMax(10, 200);
    }
  \endcode
}

 *
 * \subsection step3 Step 3: Read Sensor Request
  The function Sync() send a read request to the sensor and also return the status from the read.
  \code{.cpp}
  status_sens = Sensor_A.Sync();
  \endcode
 *
 * \subsection step4 Step 4: Read Status Handling 

 We can also manage the status of the last reading

\code{.cpp}

   switch (status_sens) {
    case (HC_SR04_OFF): {
        // Hit here when the sensor is off :(
        break;
      }
    case (HC_SR04_TIMEOUT_READ): {
        // Hit here when the sensor is not connected :(
        break;
      }
    case (HC_SR04_READ_OK): {
        // Hit here when the sensor read is betwen the valid thresholds :) !!
        break;
      }
    case (HC_SR04_UNDER_MIN): {
      // Hit here when the sensor read is under the expected thresholds :(
        break;
      }
    case (HC_SR04_OVER_MAX): {
      // Hit here when the sensor read is over  the expected thresholds :(
        break;
      }
    case (HC_SR04_READ_ERR): {
      // Hit here when the sensor read is invalid        
      break;
      }
    default:
      break;
  }
\endcode
 *
 * \subsection step5 Step 5: How to read the value from the Sensor  :V

  
The easy and simple part... in this part , we can expect a traded value in centimeters or inches according the initial setup.
\code{.cpp}
Lectura = Sensor_A.Read();
\endcode


 *
 * \subsection sample_sketch Sample Arduino Skecth
\code{.cpp}
#include <HC_SR04_lib.h>

const int Triger_Pin = 12;
const int Echo_Pin = 11;
unsigned long Lectura = 0;
unsigned char status_sens = 0;
HC_SR04Dev Sensor_A(Triger_Pin, Echo_Pin,UNITS_METRIC);

void setup() {
  Serial.begin(9600);
  // Min: 10 cm
  // Max:200 cm
  Sensor_A.SetMinMax(10, 200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  status_sens = Sensor_A.Sync();

  switch (status_sens) {
    case (HC_SR04_OFF): {
        break;
      }
    case (HC_SR04_TIMEOUT_READ): {
        break;
      }
    case (HC_SR04_READ_OK): {
        Lectura = Sensor_A.Read();
        Serial.print("Lectura OK: ");
        Serial.print(Lectura);
        Serial.println(" Centimeters");
        break;
      }
    case (HC_SR04_UNDER_MIN): {
        break;
      }
    case (HC_SR04_OVER_MAX): {
        break;
      }
    case (HC_SR04_READ_ERR): {
        break;
      }
    default:
      break;
  }

}
\endcode

 *
 * \subsection api_lib Library Methods

  ::HC_SR04Dev::Status();

  ::HC_SR04Dev::SetMinMax(unsigned long _min_range,unsigned long _max_range);
  
  ::HC_SR04Dev::Read();

  unsigned char ::HC_SR04Dev::Sync();

  ::HC_SR04Dev::HC_SR04Dev(int _trigger_pin,int _echo_pin);

 *
 * \subsection my_contact Contact Info
   Please sendme your comments or questions to esanchez.briones@yahoo.com.mx

 *
*/

#endif
