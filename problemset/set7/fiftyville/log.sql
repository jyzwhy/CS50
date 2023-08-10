-- Keep a log of any SQL queries you execute as you solve the mystery.

-- SELECT description FROM crime_scene_reports WHERE street = 'Humphrey Street' AND year = 2021 AND day = 28 AND month = 7;
-- TO get more information about the crime. I know we have three witnesses, and we can get more information from our interviews with them.

-- SELECT * FROM interviews WHERE year = 2021 AND day = 28 AND month = 7 AND transcript LIKE '%bakery%';
-- I investigated the interviews and we now havr 4 points: 1. look for cars that left the parking lot in that time frame; 2.check bank count in a bank on Leggett Street has transacions recorded on the same day; 3. check who odered a earliest flight out of Fiftyville the day after 7.28; 4. As the thief leaving the bakery(10:15am), he called someone.

-- SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit';
-- I get all the lincenes of cars left in that time frame.

-- SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- I found all the accounts that met the criteria.

-- SELECT * FROM airports WHERE city = 'Fiftyville';
-- I got the airport id of the airport in Fiftyville which is 8.

-- SELECT id FROM flights WHERE year = 2021 AND day = 29 AND month = 7 AND origin_airport_id = 8 AND destination_airport_id != 8 ORDER BY hour, minute LIMIT 1;
-- I got the flight id.

-- SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60);
-- I got the phone numbers.

SELECT name FROM people p
JOIN passengers pa ON p.passport_number = pa.passport_number
JOIN bank_accounts b ON p.id = b.person_id
WHERE p.license_plate IN
	(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit')
AND b.account_number IN
	(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
AND pa.flight_id =
	(SELECT id FROM flights WHERE year = 2021 AND day = 29 AND month = 7 AND origin_airport_id = 8 AND destination_airport_id != 8 ORDER BY hour, minute LIMIT 1)
AND p.phone_number IN
	(SELECT caller FROM phone_calls WHERE year = 2021 AND month =
7 AND day = 28 AND duration < 60);
-- who is the thief?
-- Bruce.

SELECT city FROM airports
WHERE id  =
	(SELECT destination_airport_id FROM flights WHERE year = 2021 AND day = 29 AND month = 7 AND origin_airport_id = 8 AND destination_airport_id != 8 ORDER BY hour, minute LIMIT 1);
-- What city will the thief go to?
-- New York City.

SELECT name FROM people p
WHERE phone_number in
	(SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller =
	(SELECT phone_number FROM people WHERE name = 'Bruce'));
-- Who is the thief's accomplices?
-- Robin.


