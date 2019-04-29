### MO805A -  Topics on Information Retrieval
# Assignment 7

Students: 
 - [ ] Leodécio Braz - 230219
 - [ ] Vinicius Teixeira - 230223

# Files

 - assignment/convert.py - Convert the image collection in GIF format to PGM format
 - assignment/metrics.py - Calculates the Precision vs Recall and plot the graphic
 - assignment/assignment.c - Extract feature vectors for all PGM images, calculate the function distances and generate results.csv with the ordered results of distance query of each image for both measures

## Run

- Inside the assignment folder, run:
**./assignment "path_to_imagesPgm_folder" number_of_images "results.csv"**
 
	- OUTPUT:
	Generate **results.csv** with all images names closeded of each query (image).
-	To generate the Precision vs Recall graphic, run:
**python metrics.py** 

	- OUTPUT:
	Generate **precision_vs_recall.png** with the graphics of precision versus recall for the average of all querys.
