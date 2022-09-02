
# Description

# Part 1:
We create a relational database containing vehicles and their owners
we assume that one owner may have many vehicles, but a given vehicle
it always belongs to one owner. We create identifiers,
discriminating vehicles, the same we do for the owners, part of the information about the owners
include in the PESEL number (date of birth, age, gender).
-The database is created using MySQL, manually in a .sql script
-We enter several owners and vehicles this way.
-Enter the rest of the data using a Python script, using the sql_connector_puthon library.
- The user is to be able to enter both the vehicle and the user into the base, we are also adding the display.
The pesel_utils library was also used to check PESEL numbers.

Cars_DB_handler.py module


# Part 2:
Two classes: car and owner.
The methods are the same for both:
- We take data from the table, then create objects for each class and add them to the list.
- As if we convert the results from the database to python objects and finally return the list, the same for cars and owners (separate files are best)
- Config with database, can be dumped to another file type consfig.py
- Safe method - which will save the given object from the class car, insert or update the object into the database.

//Example
print (list[0].brand) # we get the output 'foo'
<br/>
list[0] = 'bar'
</br>
list[0].safe() -> will change car brand from 'foo' to 'bar'

Cars.py, Owners.py modules
