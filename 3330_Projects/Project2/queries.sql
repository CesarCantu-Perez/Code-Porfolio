SELECT ID, Maker, Model FROM plane where LastMaint > 2021-10-01;
SELECT Name, FDate FROM pilot, flightleginstance WHERE Pilot = ID;
SELECT COUNT(*) FROM reservation WHERE PassID = 1 AND SeatClass ='E';
SELECT Maker, MAX(NoOfSeats) FROM planeseats GROUP BY Maker;
SELECT name FROM passenger, reservation WHERE PassID = ID AND FDate = DateBooked;
SELECT Code, City, State, COUNT(*) FROM airport, flightleg WHERE ToA = Code GROUP BY Code;
SELECT Name FROM pilot WHERE ID = (
	SELECT Pilot FROM flightleginstance WHERE FLNO = (
		SELECT FLNO FROM flightleg WHERE FromA = (
			SELECT Code FROM airport WHERE State = 'TX')));