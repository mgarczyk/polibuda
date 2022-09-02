# Description
The application allows you to download weather data based on the visualcrossing API, the data can be downloaded immediately after
city ​​name or after geogeraphic coordinates (then they are translated into city name based on
csv file from the website (https://simplemaps.com/data/world-cities) converted to json), based on this data is displayed
temperature graphs in a given city.
Libraries required:
- os (basic)
- json (basic)
- datetime (primary)
- requests (terminal / pip install requests)
- matplotlib (terminal / pip install matplotlib)



# More information:
Project - temperature graph over several days in a given city - selected
1) Find the weather API:
a) Authorization - API documentation (account creation or something) - most often the key in headers / url param
b) Provides endpoint (minimum - latitude and longitude)
c) you can use the API as there are restrictions - you may need to create a new email (e.g. 1000 requests per day)

2) Data storage (storage - database) - N files with the name of the city and in them
a) json file (file name - this is the name of the city):

3) Change from city name to latitude and longitude
a) There may be an API that will return the width / length of the given city.
b) Or find a database where it will be listed for a given city.
c) You can find an API that will not search by latitude and longitude, but by the name of the city (probably the easiest)

4) Chart - MATPLOTLIB - temperature chart from date

5) User:
a) get data /get:
-by name
-by geographical coordinates
b) displays /disp
-chart
c) /end - exit
