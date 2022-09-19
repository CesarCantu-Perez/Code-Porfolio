/* Name: Cesar Cantu-Perez
   ID#:  1001463763
   Due:  4/7/2022
 */
 
/*This is an executable script for CSE 3330, Lab 1*/
 
/*Creating the tables from the given schema*/

CREATE TABLE Plane (
	ID INTEGER,
	Maker VARCHAR(50),
	Model VARCHAR(50),
	LastMaint DATE,
	LastMaintA VARCHAR(50),
    PRIMARY KEY (ID)
);

CREATE TABLE PlaneType (
	Maker VARCHAR(50),
	Model VARCHAR(50),
	FlyingSpeed REAL,
	GroundSpeed REAL,
    PRIMARY KEY (Maker, Model)
);

CREATE TABLE FlightLeg (
	FLNO INTEGER,
	Seq VARCHAR(50),
	FromA VARCHAR(50), 
	ToA VARCHAR(50),
	DeptTime TIME, 
	ArrTime TIME, 
	Plane INTEGER,
    PRIMARY KEY (FLNO, Seq)
);

CREATE TABLE PlaneSeats (
	Maker VARCHAR(50), 
	Model VARCHAR(50), 
	SeatType VARCHAR(50), 
	NoOfSeats INTEGER,
    PRIMARY KEY (Maker, Model, SeatType)
);

CREATE TABLE FlightLegInstance (
	Seq VARCHAR(50), 
	FLNO INTEGER, 
	FDate DATE, 
	ActDept TIME, 
	ActArr TIME, 
	Pilot INTEGER,
    PRIMARY KEY (Seq, FLNO, FDate)
);

CREATE TABLE Airport (
	Code VARCHAR(50), 
	City VARCHAR(50), 
	State VARCHAR(50),
    PRIMARY KEY (Code)
);

CREATE TABLE Flight (
	FLNO INTEGER,
	Meal VARCHAR(50), 
	Smoking VARCHAR(50),
    PRIMARY KEY (FLNO)
);

CREATE TABLE Pilot (
	ID INTEGER, 
	Name VARCHAR(50), 
	DateHired DATE,
    PRIMARY KEY (ID)
);

CREATE TABLE FlightInstance (
	FLNO INTEGER, 
	FDate DATE,
    PRIMARY KEY (FLNO, FDate)
);

CREATE TABLE Reservation (
	PassID INTEGER,
	FLNO INTEGER, 
	FDate DATE, 
	FromA VARCHAR(50), 
	ToA VARCHAR(50), 
	SeatClass VARCHAR(50), 
	DateBooked DATE, 
	DateCancelled DATE,
    PRIMARY KEY (PassID, FLNO, FDate)
);

CREATE TABLE Passenger (
	ID INTEGER, 
	Name VARCHAR(50), 
	Phone VARCHAR(50),
    PRIMARY KEY (ID)
);

/*Changing some attributes to foreign keys*/
ALTER TABLE FlightLeg
ADD FOREIGN KEY (Plane) REFERENCES Plane(ID);

ALTER TABLE FlightLeg
ADD FOREIGN KEY (FromA) REFERENCES Airport(Code);

ALTER TABLE FlightLeg
ADD FOREIGN KEY (ToA) REFERENCES Airport(Code);

ALTER TABLE FlightLeg
ADD FOREIGN KEY (FLNO) REFERENCES Flight(FLNO);

ALTER TABLE Plane
ADD FOREIGN KEY (Maker, Model) REFERENCES PlaneType(Maker, Model);

ALTER TABLE Plane
ADD FOREIGN KEY (LastMaintA) REFERENCES Airport(Code);

ALTER TABLE PlaneSeats
ADD FOREIGN KEY (Maker, Model) REFERENCES PlaneType(Maker, Model);

ALTER TABLE FlightLegInstance
ADD FOREIGN KEY (FLNO, Seq) REFERENCES FlightLeg(FLNO, Seq);

ALTER TABLE FlightLegInstance
ADD FOREIGN KEY (FLNO, FDate) REFERENCES FlightInstance(FLNO, FDate);

ALTER TABLE FlightLegInstance
ADD FOREIGN KEY (Pilot) REFERENCES Pilot(ID);

ALTER TABLE FlightInstance
ADD FOREIGN KEY (FLNO) REFERENCES Flight(FLNO);

ALTER TABLE Reservation
ADD FOREIGN KEY (FromA) REFERENCES Airport(Code);

ALTER TABLE Reservation
ADD FOREIGN KEY (ToA) REFERENCES Airport(Code);

ALTER TABLE Reservation
ADD FOREIGN KEY (FLNO, FDate) REFERENCES FlightInstance(FLNO, FDate);

ALTER TABLE Reservation
ADD FOREIGN KEY (PassID) REFERENCES Passenger(ID);

/*Inserting data into the tables*/

INSERT INTO PlaneType (Maker, Model, FlyingSpeed, GroundSpeed)
VALUES ('Boeing', '737_MAX', 650.33, 320.06);

INSERT INTO PlaneType (Maker, Model, FlyingSpeed, GroundSpeed)
VALUES ('Boeing', '300F', 400.74, 200.50);

INSERT INTO PlaneType (Maker, Model, FlyingSpeed, GroundSpeed)
VALUES ('Airbus', 'A321', 321.32, 150.44);

INSERT INTO Airport (Code, City, State)
VALUES ('Mech-133', 'Dallas', 'TX');

INSERT INTO Airport (Code, City, State)
VALUES ('Fix-676', 'Seattle', 'WA');

INSERT INTO Airport (Code, City, State)
VALUES ('Field-002', 'Fort Worth', 'TX');

INSERT INTO Plane (ID, Maker, Model, LastMaint, LastMaintA)
VALUES (25, 'Boeing', '737_MAX', '2020-08-04', 'Mech-133');

INSERT INTO Plane (ID, Maker, Model, LastMaint, LastMaintA)
VALUES (13, 'Boeing', '300F', '2022-01-05', 'Fix-676');

INSERT INTO Plane (ID, Maker, Model, LastMaint, LastMaintA)
VALUES (2, 'Airbus', 'A321', '2021-11-30', 'Field-002');

INSERT INTO PlaneSeats (Maker, Model, SeatType, NoOfSeats)
VALUES ('Boeing', '737_MAX', 'Leather', 320);

INSERT INTO PlaneSeats (Maker, Model, SeatType, NoOfSeats)
VALUES ('Boeing', '300F', 'Fur', 200);

INSERT INTO PlaneSeats (Maker, Model, SeatType, NoOfSeats)
VALUES ('Airbus', 'A321', 'Recliners', 150);

INSERT INTO Flight (FLNO, Meal, Smoking)
VALUES (332, 'Popcorn','No');

INSERT INTO Flight (FLNO, Meal, Smoking)
VALUES (151, 'Hamburger','No');

INSERT INTO Flight (FLNO, Meal, Smoking)
VALUES (202, 'Steak','Yes');

INSERT INTO FlightInstance (FLNO, FDate)
VALUES (332, '2022-04-11');

INSERT INTO FlightInstance (FLNO, FDate)
VALUES (151, '2022-04-13');

INSERT INTO FlightInstance (FLNO, FDate)
VALUES (202, '2022-04-14');

INSERT INTO FlightLeg (FLNO, Seq, FromA, ToA, DeptTime, ArrTime, Plane)
VALUES (332, '1', 'Field-002', 'Mech-133', '08:00:00', '10:00:00', 25);

INSERT INTO FlightLeg (FLNO, Seq, FromA, ToA, DeptTime, ArrTime, Plane)
VALUES (151, '2', 'Mech-133', 'Fix-676', '12:00:00', '16:00:00', 13);

INSERT INTO FlightLeg (FLNO, Seq, FromA, ToA, DeptTime, ArrTime, Plane)
VALUES (202, '1', 'Fix-676', 'Field-002', '14:00:00', '18:00:00', 2);

INSERT INTO Passenger (ID, Name, Phone)
VALUES (1332, 'Bob Marcus', '676-800-1232');

INSERT INTO Passenger (ID, Name, Phone)
VALUES (3330, 'Jenny Ring', '312-564-1130');

INSERT INTO Passenger (ID, Name, Phone)
VALUES (6854, 'Carl Polinsky', '798-841-9563');

INSERT INTO Reservation (PassID, FLNO, FDate, FromA, ToA, SeatClass, DateBooked, DateCancelled)
VALUES (1332, 332, '2022-04-11','Field-002', 'Mech-133', 'Economy', '2022-03-08','2022-04-01');

INSERT INTO Reservation (PassID, FLNO, FDate, FromA, ToA, SeatClass, DateBooked)
VALUES (3330, 151, '2022-04-13', 'Mech-133', 'Fix-676', 'Economy', '2022-02-27');

INSERT INTO Reservation (PassID, FLNO, FDate, FromA, ToA, SeatClass, DateBooked)
VALUES (6854, 202, '2022-04-14','Fix-676', 'Field-002', 'First', '2021-11-20');

INSERT INTO Pilot (ID, Name, DateHired)
VALUES (101, 'Carrie Flyer', '2001-08-12');

INSERT INTO Pilot (ID, Name, DateHired)
VALUES (180, 'Connor Ayers', '1998-06-22');

INSERT INTO Pilot (ID, Name, DateHired)
VALUES (204, 'Dalton Skye', '2012-12-04');

INSERT INTO FlightLegInstance (Seq, FLNO, FDate, ActDept, ActArr, Pilot)
VALUES ('1', 332, '2022-04-11', '08:30:00', '10:45:00', 101);

INSERT INTO FlightLegInstance (Seq, FLNO, FDate, ActDept, ActArr, Pilot)
VALUES ('2', 151, '2022-04-13', '12:15:00', '15:50:00', 180);

INSERT INTO FlightLegInstance (Seq, FLNO, FDate, ActDept, ActArr, Pilot)
VALUES ('1', 202, '2022-04-14', '14:50:00', '19:20:00', 204);


