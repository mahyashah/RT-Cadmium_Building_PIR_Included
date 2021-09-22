This folder contains the Building Controller model implemented in ECadmium
For running this model, I had cadmium version 3, 29 June 2007 installed.
To download the whole cadmium environment run the following commad in your terminal by pressing "Ctrl+alt+t" after installing the required packages.
cd CADMIUM/
git clone https://github.com/SimulationEverywhere/Cadmium-Simulation-Environment.git
cd Cadmium-Simulation-Environment
git submodule update --init --recursive
For more information about the installation process and how to install required packages go to Cadmium manual provided in the link below.
http://www.sce.carleton.ca/courses/sysc-5104/lib/exe/fetch.php?media=cadmium.pdf

For complete explanation of the model refer the document "report.pdf".
	
/*************/
/****STEPS****/
/*************/

1 - Update include paths in all the makefiles in this folder and subfolders. You need to update the following lines:
	INCLUDECADMIUM=-I ../../cadmium/include
    Update the relative path to cadmium/include from the folder where the makefile is. You need to take into account where you copied the folder during the installation process
	Example: INCLUDECADMIUM=-I ../../cadmium/include
    
2 - Run the top model
	1 - Open the terminal. Press in your keyboard Ctrl+Alt+t
	2 - Set the command prompt in the top_model folder. To do so, type in the terminal the path to this folder.
		Example: cd ../../top_model
	3 - To compile the model, type in the terminal:
		make clean; make all
	4 - To run the model, type in the terminal "./NAME_OF_THE_COMPILED_FILE". For this test you need to type: ./SUHA_BOT_TOP
	5 - To check the output of the model, open "outputs" under top_model and check all the text files.

