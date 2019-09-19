/* This program sets up the relationships amongst the 5 fundamental entities for a food-
   truck tracker, and then instantiates them as an example. */

/*
  time gcc -o a1 a1.c
*/

#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct tenant {
  string name, phone, website;
} tenant;

typedef struct truck {
  string license;
  tenant* tenant;
} truck;

typedef struct location {
  string name, address;
  int longitude, latitude;
} location;

typedef struct booking {
  truck* truck;
  location* location;
  int start, end;
} booking;

typedef struct user {
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

user new_user(string name) {
  user out = {.name = name};

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
  printf("New booking is for truck '%s' at '%s'\n",
	 b1.truck->license,
	 b1.location->name);

  // Create user
  user u1 = new_user("Bob");
  u1.bookings = &b1;
  printf("New user '%s' with bookings\n- %d\n", u1.name, u1.bookings->start);

  // Learn how pointers to pointers function as a list
  booking** all_bookings = malloc(8 * sizeof(booking*));

  booking b2 = new_booking(&tr1, &l1, 1568866334, 1568991601);
  booking b3 = new_booking(&tr1, &l1, 1568866335, 1568991602);
  booking b4 = new_booking(&tr1, &l1, 1568866336, 1568991603);
  booking b5 = new_booking(&tr1, &l1, 1568866337, 1568991604);

  all_bookings[0] = &b1;
  all_bookings[1] = &b2;
  all_bookings[2] = &b3;
  all_bookings[3] = &b4;
  all_bookings[4] = &b5;

  for(int i = 0; all_bookings[i] != NULL; i++) {
    printf("idx %d starts at: %d\n", i, all_bookings[i]->start);
  }
}
