-- Keep a log of any SQL queries you execute as you solve the mystery.
-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.
SELECT description
FROM crime_scene_reports
WHERE day=28 AND month=7 AND year=2020 AND street="Chamberlin Street"

-- Work with the description
SELECT transcript
FROM interviews
WHERE day = "28" AND month = "7" AND year = "2020" AND transcript like "%courthouse%"

-- Working with the first transcript
SELECT name
FROM people
JOIN courthouse_security_logs ON peolpe.license_plate = courthouse_security_logs.license_plate
WHERE day = "28" AND month = "7" AND hour ="10" AND minute >= "15" AND minute < "25" AND activity = "exit";

-- Suspects: Patrick, Ernest, Amber, Danielle, Roger, Elizabeth, Russell, Evelyn

-- Working with the second transcript
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
 day= "28" AND year = "2020" AND month= "7" AND transaction_type="withdraw" AND atm_location = "Fifer Street";

-- Suspects: Danielle, Bobby, Madison, Ernest, Roy, Elizabeth, Victoria, Russel

-- By now, the names that appeared in both cases are: Ernest, Danielle, Elizabeth, Russel

-- Working with the third transcript
FROM people
JOIN passengers ON people.passport_number=passengers.passport_number
WHERE flight_id = (
    SELECT id
    FROM flights
    WHERE day = "29" AND month = "7" AND year = "2020"
    ORDER BY hour, minute
    LIMIT 1
);

-- Suspects: Doris, Roger, Ernest, Edward, Evelyn, Madison, Bobby, Danielle

-- By now, our main suspects are Ernest and Danielle

SELECT DISTINCT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE day = "28" AND month = "27" AND year = "2020" AND duration < "60"

-- Suspects: Roger, Evelyn, Ernest, Madison, Russel, Kimberly, Bobby, Victoria

-- thief is Ernest!

SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE year ="2020" AND month = "7" AND day = "29"
    ORDER BY hour, minute
    LIMIT 1
);

-- The thief ESCAPED TO: London

SELECT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller = (
    SELECT phone_number
    FROM people
    WHERE name = "Ernest"
);

-- The ACCOMPLICE is: Berthold