#ifndef __GarageControl_h_
#define __GarageControl_h_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// This is the list of recognized commands. These can be commands that can either be sent or received. 
// In order to receive, attach a callback function to these events
enum GC
{
  GC_Acknowledge,     // 0
  GC_Error,           // 1
  GC_Temperature,     // 2
  GC_DoorStatus,      // 3
  GC_PushButton,      // 4
  GC_CloseDoor,       // 5
  GC_OpenDoor,        // 6
  GC_GetTemperature,  // 7
  GC_GetDoorStatus,   // 8
};

enum DS
{
  DS_Unknown, // 0
  DS_Open,    // 1
  DS_Opening, // 2
  DS_Closed,  // 3
  DS_Closing  // 4
};

struct Response
{
  GC code;
  uint32_t value;
};

String toString(DS door)
{
  switch( door )
  {
    case DS_Unknown:
      return "Unknown";
    case DS_Open:
      return "Open";
    case DS_Opening:
      return "Opening";
    case DS_Closed:
      return "Closed";
    case DS_Closing:
      return "Closing";
  }
  
  return "??";
}

Print & operator<<(Print & ps, GC e)
{
  switch( e )
  {
    case GC_Acknowledge:
      ps.print("GC_Acknowledge");
    break;

    case GC_Error:
      ps.print("GC_Error");
    break;
   
    case GC_GetTemperature:
      ps.print("GC_GetTemperature");
    break;
    
    case GC_Temperature:
      ps.print("GC_Temperature");
    break;

    case GC_GetDoorStatus:
      ps.print("GC_GetDoorStatus");
    break;
    
    case GC_DoorStatus:
      ps.print("GC_DoorStatus");
    break;

    default:
      ps.print("??");
  }
  
  ps.print(" (");
  ps.print(e);
  ps.print(")");
  
  return ps;
}

Print & operator<<(Print & ps, const Response & r)
{
  ps.print("code: ");
  ps << r.code;
  ps.print("; value: ");
  ps.print(r.value);
  
  return ps;
}

#endif // __GarageControl_h_
