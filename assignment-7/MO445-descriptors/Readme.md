### MO805A -  Topics on Information Retrieval
# Assignment 7

Students: 
 - [ ] Leodécio Braz - 230219
 - [ ] Vinicius Teixeira - 230223

# Files

 - GIF_to_PGM .py - Convert the image collection in GIF format to PGM format
 - Metrics .py - Calculates the Precision vs Recall and plot the graphic
 - Results .cvs - Ordered results of distance query of each image for both measures 

## Run

- Inside the assignment folder, run:
**./assignment "path_to_imagesPgm_folder" number_of_images "results.csv"**
 
	- OUTPUT:
	Generate **results.csv** with all images names closeded of each query (image).
-	To generate the Precision vs Recall graphic, run:
**python metrics.py** 
	-	Changing the paths of the variables:
			-	source_path
			-	path_images
			-	output_path
