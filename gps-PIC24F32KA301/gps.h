#ifndef GPS_H
#define	GPS_H

typedef struct {
    long int lat1;
    long int lat2;
    char NS;
    long int lon1;
    long int lon2;
    char WE;
    long int time1;
    long int time2;
    char texto[120];
    long int speed1;
    long int speed2;
    long int course1;
    long int course2;
    long int date;
    int valid;
} gpsdata;



extern int wait_for_gps(char * thing);

extern gpsdata gps, temp;

#endif	/* GPS_H */

