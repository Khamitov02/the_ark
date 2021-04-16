//
// Created by Amisto on 4/2/2021.
//

#ifndef THE_ARK_RESOURCES_H
#define THE_ARK_RESOURCES_H

#include <vector>


class Resources {
private:
	class Resource {
	private:
		unsigned int amount;

	public:
		Resource(unsigned int total);		                	// init user's amount of general resource
		void GetResource(unsigned int isReturned);			// add recycled junk to available resources
		void GiveResource(unsigned int isNeeded);			// remove an amount of currently used resources
		unsigned int ReturnTotal() const;
	};
	
	unsigned int consumables, components, junk, refuse, used;
	std::vector<unsigned int> used_by_services;                		// vector contains an amount of current used resources for each service
	
	double efficiencyConsumablesToComponents() const;          		// processing consumables to components // TS
	double efficiencyJunkToConsumables() const;                		// recycling junk to consumablse // TS
	double efficiencyJunkToRefuse() const;                     		// recycling junk to refuse // TS

public:
   	Resources();

	unsigned int getConsumables() const;
	unsigned int getUsed() const;
	unsigned int getJunk() const;
	unsigned int getRefuse() const;
	unsigned int getComponents() const;

	void setComponentsToUsed(unsigned int current_usage, int id); 		// method to be called by services to get resources
	void setUsedToJunk(unsigned int current_broken, int id);		// method to be called by services to return junk
	void setUsedToConsumables(unsigned int current_created, int id);	// method to be called by services to return consumables

	void init(unsigned int total);
	void processYear(); 							// the process of year's changing of all resources' categories
};


#endif //THE_ARK_RESOURCES_H
