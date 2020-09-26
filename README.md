# Search algorithms on Google Maps Coordinates

This programm performs search using all the popular search algorithms to find the fastest path between 2 cities of Greece.
Algorithms implemented:

**1. Best First Search**

__2. A* KM: Using the straight line distance as a cost function__

__3. A* MIN: Using the time needed calculated using the maximum speed that someone need to run these roads__

**4. BFS**

**5. DFS**

**6. Uniform Search**

The **all_Roads.txt** contains all the majow cities of greece with their coordinates from Google Maps 
as well as big roads with their names connecting them and also information about the time  and KM needed according 
to Google to complete this route. I also added 42 cities and villages from Pieria and Thesprotia(Greece).

The programm contains functions to add,remove road and cities, search cities and all the auxiliary functins needed.

Example output:

Give starting point: Katerini
Give destination: Peristash
-----------------------------------------------------------------------------------
Best FS(27): Katerini->Aronas->Peristash
 Using road 36: EO Aronas Mosxopotamou
 Using road 13: EO Aronas Mosxopotamou
Total KM: 19.7 KM, total time: 27 minutes.
A* KM(9): Katerini->Peristash
 Using road 15: Leonida Iasonidi
Total KM: 3.3 KM, total time: 5 minutes.
A* MIN(9): Katerini->Peristash
 Using road 15: Leonida Iasonidi
Total KM: 3.3 KM, total time: 5 minutes.
BFS: Katerini -> Litochoro -> Trapezounta -> Lofos -> Raxh -> Rhtini ->
Mosxopotamos -> Aronas -> Andromaxi -> Peristash
 Using road: Palia ethniki odo Thessalonikis
 Using road: Ethniki odo Athinon Thessalonikis
 Using road: Ethniki odo Athinon Thessalonikis
 Using road: EO Katerinis Litochorou
 Using road: EO Katerinis Litochorou
 Using road: EO Elatochoriou
 Using road: EO Aronas Mosxopotamou
 Using road: EO Aronas Mosxopotamou
 Using road: EO Aronas Mosxopotamou
Total KM(27): 206.6 km, total_time= 222 minutes
DFS: Katerini -> Litochoro -> Nea Trapezounta -> Trapezounta -> Lofos -> Agios
Dhmitrios -> Brontou -> Korinos -> Nea Trapezounta -> Litochoro -> Lagoraxh ->
Litochoro -> Raxh -> Rhtini -> Agios Dhmhtrios -> Andromaxi -> Plaka ->
Mosxopotamos -> Paralia -> Aronas -> PeristashAndromaxi -> Peristash Using
road: Paradromo Athinon Thessalonikis
 Using road: Ethniki odo Athinon Thessalonikis
 Using road: PEO Athinon Thessalonikis
 Using road: EO13
 Using road: EO Katerinis Ellasonas
 Using road: Egnatia Odos Athinon Thessalonikis
 Using road: Palia Ethniki odo Athinon Thessalonikis
 Using road: Palia ethniki odo Athinon Thessalonikis
 Using road: EO Katerinis Litochorou
 Using road: EO Katerinis Ellasonas
 Using road: EO Katerinis Litochorou
 Using road: E013
 Using road: EO13
 Using road: EO Katerinis Ellasonas
 Using road: EO Elatochoriou
 Using road: Ethniki odo Athinon Thessalonikis
 Using road: EO Aronas Mosxopotamou
 Using road: EO Aronas Mosxopotamou
 Using road: EO Aronas Mosxopotamou
 Using road: EO Aronas Mosxopotamou
 Using road: EO13
 Using road: Leonida Iasonidi
Total KM(0): 0 KM, total minutes: 0 minutes.
Uniform (9): Katerini->Peristash
 Using road 15: Leonida Iasonidi
Total KM: 3.3 KM, total time: 5 minutes.
