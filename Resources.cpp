//
// Created by Amisto on 4/2/2021.
//

#include "Resources.h"
#include "TheArk.h"
#include "TechnicalService.h"
#include <vector>

Resources::Resource::Resource(unsigned int total) : amount(total) 
{

}

void Resources::Resource::GetResource(unsigned int isReturned) {
	this->amount += isReturned;
}

void Resources::Resource::GiveResource(unsigned int isNeeded) {
	this->amount -= isNeeded;
}

unsigned int Resources::Resource::ReturnTotal() const {
	return this->amount;
}

unsigned int Resources::getComponents() const {
	return components;
}

unsigned int Resources::getRefuse() const {
	return refuse;
}

unsigned int Resources::getConsumables() const {
	return consumables;
}

unsigned int Resources::getUsed() const {
	return used;
}

unsigned int Resources::getJunk() const {
	return junk;
}

Resources::Resources() : consumables(0), components(0), used_by_services({0, 0, 0, 0, 0, 0}), used(0), junk(0), refuse(0)
{

}

void Resources::processYear() {
	consumables *= efficiencyConsumablesToComponents()/100;
	components  *= efficiencyConsumablesToComponents()/100;
	consumables *= efficiencyJunkToConsumables()/100;
	junk        *= efficiencyJunkToConsumables()/100;
	junk        *= efficiencyJunkToRefuse()/100;
	refuse      *= efficiencyJunkToRefuse()/100;	
}

void Resources::setComponentsToUsed(unsigned int current_usage, int id) {
	used_by_services[id] += current_usage;
	components           -= current_usage;
	used                 += current_usage;
}

void Resources::setUsedToJunk(unsigned int current_broken, int id) {
	junk                 += current_broken;
	used_by_services[id] -= current_broken;
	used                 -= current_broken;
}

void Resources::setUsedToConsumables(unsigned int current_created, int id) {
	consumables          += current_created;
	used_by_services[id] -= current_created;
	used                 -= current_created;
}

double Resources::efficiencyConsumablesToComponents() const {
	return TheArk::get_instance()->getTechnicalService()->efficiencyConsumablesToComponents();
}

double Resources::efficiencyJunkToConsumables() const {
	return TheArk::get_instance()->getTechnicalService()->efficiencyJunkToConsumables();
}

double Resources::efficiencyJunkToRefuse() const {
	return TheArk::get_instance()->getTechnicalService()->efficiencyJunkToRefuse();
}

void Resources::init(unsigned int total) {
	Resource GeneralResources(total);
	consumables = 0.3 * total;
	components  = 0.2 * total;
}
