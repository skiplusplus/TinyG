/*
 * hardware.h - hardware configuration values 
 *			 	Reflects system hardware dependencies 
 *			 	Application (software) globals are in tinyg.h
 * 
 * Part of TinyG project
 * Copyright (c) 2010 Alden S. Hart, Jr.
 *
 * TinyG is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your 
 * (option) any later version.
 *
 * TinyG is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with TinyG  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef hardware_h
#define hardware_h

void hw_init(void);						// master hardware init

/* CPU clock */	

#undef F_CPU							// set for delays
#define F_CPU 32000000UL				// should always precede <avr/delay.h>

// default hardwired settings in - chose one:
#define __LEADSCREW_20					// 1/4" 20 leadscrew table
//#define __MAKERBOT						// makerbot settings

// Clock Crystal Config. Pick one:
//#define __CLOCK_INTERNAL_32MHZ TRUE	// use internal oscillator
//#define __CLOCK_EXTERNAL_8MHZ	TRUE	// uses PLL to provide 32 MHz system clock
#define __CLOCK_EXTERNAL_16MHZ TRUE		// uses PLL to provide 32 MHz system clock

/* Stepper Ports \- motor port bits are:
 *	b7	(in) max limit switch  			// alt: (out) spindle direction on A axis
 *	b6	(in) min limit switch			// alt: (out) spindle enable on A axis
 *	b5	(out) output bit for encoder port
 *	b4	(out) microstep 1
 *	b3	(out) microstep 0 
 *	b2	(out) motor enable 	(CLR = Enabled)
 *	b1	(out) direction		(CLR = Clockwise)
 *	b0	(out) step			(SET is step,  CLR is rest)
 */

enum cfgPortBits {						// motor control port bit positions
	STEP_BIT_bp,						// bit 0
	DIRECTION_BIT_bp,					// bit 1
	MOTOR_ENABLE_BIT_bp,				// bit 2
	MICROSTEP_BIT_0_bp,					// bit 3
	MICROSTEP_BIT_1_bp,					// bit 4
	ENCODER_OUT_BIT_bp,					// bit 5 (4 encoder bits; 1 from each axis)
	MIN_LIMIT_BIT_bp,					// bit 6
	MAX_LIMIT_BIT_bp					// bit 7
};

#define STEP_BIT_bm				(1<<STEP_BIT_bp)
#define DIRECTION_BIT_bm		(1<<DIRECTION_BIT_bp)
#define MOTOR_ENABLE_BIT_bm 	(1<<MOTOR_ENABLE_BIT_bp)
#define MICROSTEP_BIT_0_bm		(1<<MICROSTEP_BIT_0_bp)
#define MICROSTEP_BIT_1_bm		(1<<MICROSTEP_BIT_1_bp)
#define ENCODER_OUT_BIT_bm		(1<<ENCODER_OUT_BIT_bp)		
#define MIN_LIMIT_BIT_bm		(1<<MIN_LIMIT_BIT_bp)
#define MAX_LIMIT_BIT_bm		(1<<MAX_LIMIT_BIT_bp) // motor control port bit masks

/*
 * BASELINE HARDWARE CONFIGURATION VALUES (overridden by EEPROM values)
 */

/* Gcode power-on defaults */
#define GCODE_PLANE	CANON_PLANE_XY
#define GCODE_UNITS 1					// mm
#define GCODE_TOOL 1
#define GCODE_FEED_RATE 400				// mm/min
#define GCODE_SPINDLE_SPEED 1500		// rpm

/* non-axis machine defaults */

#define MM_PER_ARC_SEGMENT 0.02
#define HOMING_MODE 0					// unsupported
#define A_RADIUS RADIAN					// makes mm/min = degrees/min on conversion

#ifdef __LEADSCREW_20

/* Microstep defaults - chose a value on the top line */
#define MICROSTEP_MODE 8				// Choose one of: 8, 4, 2, 1
#define SEEK_STEPS 1000
#define FEED_STEPS 1000
//#define STEP_ANGLE 1.8
#define STEP_ANGLE 0.9
#define TRAVEL_PER_REV 2.54	 		// 2.54=10 TPI screw, 1.27=20 TPI screw
#define TRAVEL_OFFSET -100

#define X_MAP_AXIS X					// standard axis mappings
#define Y_MAP_AXIS Y
#define Z_MAP_AXIS Z
#define A_MAP_AXIS A

#define X_AXIS_MODE 0					// 0=normal mode
#define Y_AXIS_MODE 0
#define Z_AXIS_MODE 0					// 1= Z disable (for dry runs)
#define A_AXIS_MODE 0					// 1= A extruder mode (2= coordinated spindle)

#define X_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS // max whole steps per second for G0 motion
#define Y_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS // (motor parameter)
#define Z_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS
#define A_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS

#define X_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS // max whole steps per sec for feed motion
#define Y_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS // (motor parameter)
#define Z_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS
#define A_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS

#define X_DEGREE_PER_WHOLE_STEP	STEP_ANGLE	// degrees per whole step
#define Y_DEGREE_PER_WHOLE_STEP	STEP_ANGLE 	// (motor parameter)
#define Z_DEGREE_PER_WHOLE_STEP	STEP_ANGLE
#define A_DEGREE_PER_WHOLE_STEP	STEP_ANGLE

#define X_MICROSTEP_MODE MICROSTEP_MODE	// microstep mode 
#define Y_MICROSTEP_MODE MICROSTEP_MODE	// (stepper driver configuration parameter)
#define Z_MICROSTEP_MODE MICROSTEP_MODE
#define A_MICROSTEP_MODE MICROSTEP_MODE

#define X_POLARITY 0					// motor direction polarity
#define Y_POLARITY 0
#define Z_POLARITY 0
#define A_POLARITY 1

#define X_TRAVEL_OFFSET TRAVEL_OFFSET	// offset to zero from minimum travel
#define Y_TRAVEL_OFFSET TRAVEL_OFFSET
#define Z_TRAVEL_OFFSET TRAVEL_OFFSET
#define A_TRAVEL_OFFSET TRAVEL_OFFSET

#define X_TRAVEL_MAX 400				// full excursion from min to max 
#define Y_TRAVEL_MAX 400				// (robot parameter)
#define Z_TRAVEL_MAX 100
#define A_TRAVEL_MAX -1					// -1 is no limit (typ for rotary axis)

#define X_TRAVEL_WARN 400				// full excursion from min to max 
#define Y_TRAVEL_WARN 400				// (robot parameter)
#define Z_TRAVEL_WARN 100
#define A_TRAVEL_WARN -1				// -1 is no limit (typ for rotary axis)

#define X_TRAVEL_REVOLUTION TRAVEL_PER_REV	// 10 TPI leadscrew machine
#define Y_TRAVEL_REVOLUTION TRAVEL_PER_REV	// (robot parameter)
#define Z_TRAVEL_REVOLUTION TRAVEL_PER_REV
#define A_TRAVEL_REVOLUTION TRAVEL_PER_REV	// degrees moved per motor revolution

#define X_POWER_MODE TRUE				// 1=low power idle enabled 
#define Y_POWER_MODE TRUE				// (robot parameter)
#define Z_POWER_MODE TRUE
#define A_POWER_MODE TRUE

#define X_LIMIT_MODE TRUE				// 1=limit switches present and enabled
#define Y_LIMIT_MODE TRUE				// (robot parameter)
#define Z_LIMIT_MODE TRUE
#define A_LIMIT_MODE FALSE

#endif	// _LEADSCREW_20

#ifdef __MAKERBOT

/* Microstep defaults - chose a value on the top line */
#define MICROSTEPS 8					// Choose one of: 8, 4, 2, 1
#define SEEK_STEPS 500
#define FEED_STEPS 500
#define STEP_ANGLE 1.8

#define X_MAP_AXIS X					// default axis mappings
#define Y_MAP_AXIS Y
#define Z_MAP_AXIS Z
#define A_MAP_AXIS A

#define X_AXIS_MODE 0
#define Y_AXIS_MODE 0
#define Z_AXIS_MODE 0
#define A_AXIS_MODE 0

#define X_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS // max whole steps per second for G0 motion
#define Y_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS // (motor parameter)
#define Z_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS
#define A_SEEK_WHOLE_STEPS_PER_SEC SEEK_STEPS

#define X_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS // max whole steps per sec for feed motion
#define Y_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS // (motor parameter)
#define Z_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS
#define A_FEED_WHOLE_STEPS_PER_SEC FEED_STEPS

#define X_DEGREE_PER_WHOLE_STEP	STEP_ANGLE	// degrees per whole step
#define Y_DEGREE_PER_WHOLE_STEP	STEP_ANGLE 	// (motor parameter)
#define Z_DEGREE_PER_WHOLE_STEP	STEP_ANGLE
#define A_DEGREE_PER_WHOLE_STEP	STEP_ANGLE

#define X_MICROSTEP_MODE MICROSTEP_MODE	// microstep mode 
#define Y_MICROSTEP_MODE MICROSTEP_MODE	// (stepper driver configuration parameter)
#define Z_MICROSTEP_MODE MICROSTEP_MODE
#define A_MICROSTEP_MODE MICROSTEP_MODE

#define X_POLARITY 0					// motor direction polarity
#define Y_POLARITY 0
#define Z_POLARITY 1
#define A_POLARITY 1

#define X_TRAVEL_OFFSET 0				// offset to zero from minimum travel
#define Y_TRAVEL_OFFSET 0
#define Z_TRAVEL_OFFSET 0
#define A_TRAVEL_OFFSET 0

#define X_TRAVEL_MAX 100				// full excursion from min to max 
#define Y_TRAVEL_MAX 100				// (robot parameter)
#define Z_TRAVEL_MAX 150
#define A_TRAVEL_MAX -1					// -1 is no limit (typ for rotary axis)

#define X_TRAVEL_WARN 400				// full excursion from min to max 
#define Y_TRAVEL_WARN 400				// (robot parameter)
#define Z_TRAVEL_WARN 100
#define A_TRAVEL_WARN -1				// -1 is no limit (typ for rotary axis)

#define X_TRAVEL_REVOLUTION 33			// Makerbot settings
#define Y_TRAVEL_REVOLUTION 33			// (robot parameter)
#define Z_TRAVEL_REVOLUTION 1.27
#define A_TRAVEL_REVOLUTION 1.27

#define X_POWER_MODE TRUE				// 1=low power idle enabled 
#define Y_POWER_MODE TRUE				// (robot parameter)
#define Z_POWER_MODE TRUE
#define A_POWER_MODE TRUE

#define X_LIMIT_MODE TRUE				// 1=limit switches present and enabled
#define Y_LIMIT_MODE TRUE				// (robot parameter)
#define Z_LIMIT_MODE TRUE
#define A_LIMIT_MODE FALSE

#endif	// __MAKERBOT


/* Derived Values */

#define X_SEEK_STEPS_PER_SEC (X_SEEK_WHOLE_STEPS_PER_SEC * X_MICROSTEPS)
#define Y_SEEK_STEPS_PER_SEC (Y_SEEK_WHOLE_STEPS_PER_SEC * Y_MICROSTEPS)
#define Z_SEEK_STEPS_PER_SEC (Z_SEEK_WHOLE_STEPS_PER_SEC * Z_MICROSTEPS)
#define A_SEEK_STEPS_PER_SEC (A_SEEK_WHOLE_STEPS_PER_SEC * A_MICROSTEPS)

#define X_FEED_STEPS_PER_SEC (X_FEED_WHOLE_STEPS_PER_SEC * X_MICROSTEPS)
#define Y_FEED_STEPS_PER_SEC (Y_FEED_WHOLE_STEPS_PER_SEC * Y_MICROSTEPS)
#define Z_FEED_STEPS_PER_SEC (Z_FEED_WHOLE_STEPS_PER_SEC * Z_MICROSTEPS)
#define A_FEED_STEPS_PER_SEC (A_FEED_WHOLE_STEPS_PER_SEC * A_MICROSTEPS)

#define X_DEGREE_PER_STEP (X_DEGREE_PER_WHOLE_STEP / X_MICROSTEPS)
#define Y_DEGREE_PER_STEP (Y_DEGREE_PER_WHOLE_STEP / Y_MICROSTEPS)
#define Z_DEGREE_PER_STEP (Z_DEGREE_PER_WHOLE_STEP / Z_MICROSTEPS)
#define A_DEGREE_PER_STEP (A_DEGREE_PER_WHOLE_STEP / A_MICROSTEPS)

#endif