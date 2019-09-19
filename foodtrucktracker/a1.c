/*
  time gcc -o a1 a1.c
*/

#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct {
  string name, phone, website;
} tenant;

typedef struct {
  string license;
  tenant* tenant;
} truck;

typedef struct {
  string name, address;
  int longitude, latitude;
} location;

typedef struct {
  truck* truck;
  location* location;
  int start, end;
} booking;

typedef struct {
  string name;
  booking* bookings;
} user;

tenant new_tenant(string name) {
  tenant out = {.name = name};

  return out;
}

truck new_truck_for_tenant(tenant* tenant, string license) {
  truck out = {.tenant = tenant, .license = license};

  return out;
}

location new_location(string name, int latitude, int longitude) {
  location out = {.name = name, .latitude = latitude, .longitude = longitude};

  return out;
}

booking new_booking(truck* truck, location* location, int start, int end) {
  booking out = {
		 .truck = truck,
		 .location = location,
		 .start = start,
		 .end = end
  };

  return out;
}

int
main(int argc, char **argv) {
  // Create tenant
  tenant a1 = new_tenant("blurb");
  printf("name is %s\n", a1.name);

  // Create truck
  truck tr1 = new_truck_for_tenant(&a1, "FOFO 443");
  printf("truck '%s' belongs to tenant '%s'\n", tr1.license, tr1.tenant->name);

  // Create location
  location l1 = new_location("The awesome spot", 437001, -794163);
  printf("Location is '%s', at (%d, %d)\n", l1.name, l1.latitude, l1.longitude);

  // Create booking
  booking b1 = new_booking(&tr1, &l1, 1568866333, 1568991600);
  printf("New booking is for truck '%s' at '%s'\n", b1.truck->license, b1.location->name);
}
