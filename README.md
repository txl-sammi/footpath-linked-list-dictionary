# Footpath Linked List Dictionary 
Project for COMP20003 Algorithms and Data Structures

The dataset comes from the City of Melbourne Open Data website, which provides a variety of data about Melbourne that you can explore and visualise online:

https://data.melbourne.vic.gov.au/

The dataset used in this project is a subset of the Footpath Steepness dataset combined with data from the Small Areas for Census of Land Use and Employment (CLUE) dataset. This dataset has been processed to simplify the geometric polygon data into additional attributes clue_sa, start lon, start lat, end lon, end lat, which can be used to approximate the footpath as a line on the map. 

A user will be able to search this dictionary to retrieve information about footpaths in Melbourne using attributes in the dataset (keys). 

A dictoinary was built by reading the data from a file and inserting each footpath record as a node in a linked list. Users will also be able to search for a key in the list, outputting any records that match the key. 
