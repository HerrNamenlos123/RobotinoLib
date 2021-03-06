//  Copyright (C) 2004-2013, Robotics Equipment Corporation GmbH

//Copyright (c) ...
//
//REC Robotics Equipment Corporation GmbH, Planegg, Germany. All rights reserved.
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY REC ROBOTICS EQUIPMENT CORPORATION GMBH �AS IS� AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL REC ROBOTICS EQUIPMENT CORPORATION GMBH
//BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
//GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
//LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//Copyright (c) ...
//
//REC Robotics Equipment Corporation GmbH, Planegg, Germany. Alle Rechte vorbehalten.
//Weiterverbreitung und Verwendung in nichtkompilierter oder kompilierter Form, mit oder ohne Ver�nderung, sind unter den folgenden Bedingungen zul�ssig:
//1) Weiterverbreitete nichtkompilierte Exemplare m�ssen das obige Copyright, diese Liste der Bedingungen und den folgenden Haftungsausschluss im Quelltext enthalten.
//2) Weiterverbreitete kompilierte Exemplare m�ssen das obige Copyright, diese Liste der Bedingungen und den folgenden Haftungsausschluss in der Dokumentation und/oder anderen Materialien, die mit dem Exemplar verbreitet werden, enthalten.
//
//DIESE SOFTWARE WIRD VON REC ROBOTICS EQUIPMENT CORPORATION GMBH OHNE JEGLICHE SPEZIELLE ODER IMPLIZIERTE GARANTIEN ZUR VERF�GUNG GESTELLT, DIE UNTER
//ANDEREM EINSCHLIESSEN: DIE IMPLIZIERTE GARANTIE DER VERWENDBARKEIT DER SOFTWARE F�R EINEN BESTIMMTEN ZWECK. AUF KEINEN FALL IST REC ROBOTICS EQUIPMENT CORPORATION GMBH
//F�R IRGENDWELCHE DIREKTEN, INDIREKTEN, ZUF�LLIGEN, SPEZIELLEN, BEISPIELHAFTEN ODER FOLGESCH�DEN (UNTER ANDEREM VERSCHAFFEN VON ERSATZG�TERN ODER -DIENSTLEISTUNGEN;
//EINSCHR�NKUNG DER NUTZUNGSF�HIGKEIT; VERLUST VON NUTZUNGSF�HIGKEIT; DATEN; PROFIT ODER GESCH�FTSUNTERBRECHUNG), WIE AUCH IMMER VERURSACHT UND UNTER WELCHER VERPFLICHTUNG
//AUCH IMMER, OB IN VERTRAG, STRIKTER VERPFLICHTUNG ODER UNERLAUBTER HANDLUNG (INKLUSIVE FAHRL�SSIGKEIT) VERANTWORTLICH, AUF WELCHEM WEG SIE AUCH IMMER DURCH DIE BENUTZUNG
//DIESER SOFTWARE ENTSTANDEN SIND, SOGAR, WENN SIE AUF DIE M�GLICHKEIT EINES SOLCHEN SCHADENS HINGEWIESEN WORDEN SIND.

#ifndef _REC_ROBOTINO_API2_OMNIDRIVE_H_
#define _REC_ROBOTINO_API2_OMNIDRIVE_H_

#include "rec/robotino/api2/defines.h"
#include "rec/robotino/api2/ComObject.h"

namespace rec
{
	namespace robotino
	{
		namespace api2
		{
			class OmniDriveImpl;

			/**
			* @brief	Calculates motor velocities for the omni drive.
			* 
			* Directional and rotational coordinates are provided and velocities
			* for the single motors are calculated.
			*
			* @see	Motor
			*/
			class
#ifdef REC_ROBOTINO_API2_CLASS_ATTRIBUTE
	REC_ROBOTINO_API2_CLASS_ATTRIBUTE
#endif
			OmniDrive : public ComObject
			{
				friend class OmniDriveImpl;
			public:
				OmniDrive();

				OmniDrive(const ComId& id);
				
				virtual ~OmniDrive();

				/** 
				* Sets the associated communication object.
				*
				* @param id The id of the associated communication object.
				* @throws	RobotinoException if given id is invalid.
				* @remark This function is thread save
				*/
				void setComId( const ComId& id );

				/**
				* @param vx		Velocity in x-direction in m/s
				* @param vy		Velocity in y-direction in m/s
				* @param omega	Angular velocity in rad/s
				* @remark This function is thread save. It should be called about every 100ms.
				*/
				void setVelocity( float vx, float vy, float omega );
				
				/**
				* @param vx		Velocity in x-direction in percent max speed
				* @param vy		Velocity in y-direction in percent max speed
				* @param omega	Angular velocity in percent max speed
				* @remark This function is thread save. It should be called about every 100ms.
				*/
				void setVelocityPercent( float vx, float vy, float omega );

				/**
				* Retrieves the layout parameters of the robots drive system from the server.
				* @param rb		Distance from robot center to wheel center in m.
				* @param rw		Radius of the wheels in m.
				* @param fctrl	Frequency of control loop measuring the speed in Hz.
				* @param gear	Gear
				* @param mer	Motor encoder resolution.
				* @throws		nothing.
				* @remark		This function is thread save
				*/
				void getDriveLayout( double* rb, double* rw, double* fctrl, double* gear, double* mer );

				/**
				* Called when the drive layout changes.
				* @param rb		Distance from robot center to wheel center in m.
				* @param rw		Radius of the wheels in m.
				* @param fctrl	Frequency of control loop measuring the speed in Hz.
				* @param gear	Gear
				* @param mer	Motor encoder resolution.
				* @remark This function is called from the thread in which Com::processEvents() is called.
				* @see Com::processEvents
				*/
				virtual void driveLayoutChangedEvent( double rb, double rw, double fctrl, double gear, double mer );

			private:
				OmniDriveImpl* _impl;
			};
		}
	}
}
#endif //_REC_ROBOTINO_API2_OMNIDRIVE_H_
