# 2DFFT
2DFFT Software Package to Measure Galactic Spiral Arm Pitch Angle

2DFFT utilizes two-dimensional fast Fourier transformations of images of spiral galaxies to isolate and measure the pitch angles of their spiral arms; this provides a quantitative way to measure this morphological feature and allows comparison of spiral galaxy pitch angle to other galactic parameters and test spiral arm genesis theories.

**IMPORTANT NOTE - This collection of software requires fourn.c from "Numerical Recipes in C" (Press et al. 1989).**

1.  Compile the various files before the first usage of the software with the following commands:

	make -f M2dfft
	make give_maximum_pitch_phase
	make scripter

    Note - give_maximum_pitch_phase is setup to for with a g77 Fortran compiler, if you use a different Fortran compiler you will need to edit the make file.

2.  Prepare galaxy images:

  a.  Preferably use .fits images.

  b.  It is desirable to first deproject images to a face-on orientation.

  c.  Crop images to square dimensions with the galaxy centered in the frame.

    I.  Maximum image size is 2048 x 2048 pixels.

    II. More powerful computers could perhaps support larger image sizes, if so, change variable DIM_X, DIM_Y, DIM_RAD, and DIM_THT in 2dftt.c.

  d.  Convert images to an ASCII .txt file format.

3.  Create an input file consisting of image .txt files, keywords (filename prefix for output files), and outer radii of the galaxies in pixels for scripter.ccp to read with the following format:

> [blank line]
> 
> image_textfile_1,keyword_1,outer_radius_1
> 
> image_textfile_2,keyword_2,outer_radius_2
> 
> image_textfile_3,keyword_3,outer_radius_3
> 
> image_textfile_etc,keyword_etc,outer_radius_etc
> 
> [blank line]

See the file included file "input.txt" as a template for input files.

4.  Run scripter.cpp (e.g., ./scripter).

5.  Scripter will ask "Enter Input File Name," enter the name of the input file you created in Step 3.

6.  Scripter will then ask "Enter Output File Name," enter the name of the "script_file" which will subsequently be written.

7.  Make the script file you entered in Step 6 an executable:

	chmod +x script_file

8.  Execute the "script_file" (e.g., ./script_file).

9.  When the script has completed it will create files: keyword_m0, keyword_m1, keyword_m2, keyword_m3, keyword_m4, keyword_m5, keyword_m6. These files represent the different m harmonic modes. A set of these seven files will be created for each galaxy. In these files, the structure of the columns in a left to right fashion is:

Column 1 = m

Column 2 = "outiX_m2" where "X" is the inner radius in pixels

Column 3 = p_{max}

Column 4 = p_{max} amplitude

Column 5 = pitch angle (deg.)

Column 6 = phase angle (deg.)

**If you publish results using this code, please cite the following paper:**

Davis, B. L., Berrier, J. C., Shields, D. W, et al., Measurement of Galactic Logarithmic Spiral Arm Pitch Angle Using Two-Dimensional Fast Fourier Transform Decomposition, ApJS, 199, 33 (2012): https://doi.org/10.1088/0067-0049/199/2/33
