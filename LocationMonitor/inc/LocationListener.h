/*
 * LocationListener.h
 *
 *  Created on: Sep 16, 2014
 */

#ifndef LOCATIONLISTENER_H_
#define LOCATIONLISTENER_H_

#include <FLocations.h>

class LocationListener
	: public Tizen::Locations::ILocationProviderListener
{
public:
	LocationListener(void);
	~LocationListener(void);

	void 	OnAccuracyChanged (Tizen::Locations::LocationAccuracy accuracy);
	void 	OnLocationUpdated (const Tizen::Locations::Location &location);
	void 	OnLocationUpdateStatusChanged (Tizen::Locations::LocationServiceStatus status);
	void 	OnRegionEntered (Tizen::Locations::RegionId regionId);
	void 	OnRegionLeft (Tizen::Locations::RegionId regionId);
	void 	OnRegionMonitoringStatusChanged (Tizen::Locations::LocationServiceStatus status);

private:

};


#endif /* LOCATIONLISTENER_H_ */
