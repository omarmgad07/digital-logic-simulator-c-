#ifndef CONST_H
#define CONST_H

//This header file contains some dkefenitions to be used all over the application

//All possible actions
enum ActionType
{
	ADD_AND_GATE_2,
	ADD_OR_GATE_2,
	ADD_NAND_GATE_2,
	ADD_NOR_GATE_2,
	ADD_XOR_GATE_2,
	ADD_XNOR_GATE_2,
	ADD_3AND_GATE_2,
	ADD_3NAND_GATE_2,
	ADD_3NOR_GATE_2,
	ADD_3XOR_GATE_2,
	ADD_BUFF_GATE_2,
	ADD_NOT_GATE_2,
	ADD_Switch,
	ADD_LED,
	ADD_CONNECTION,

	ADD_Label,
	EDIT_Label,

	Create_TruthTable,

	Change_Switch,

	SELECT,

	DEL,
	MOVE,

	SAVE,
	LOAD,

	UNDO,
	REDO,
	COPY,
	PASTE,
	CUT,

	DSN_MODE,
	SIM_MODE,

	EXIT,

	STATUS_BAR,
	DSN_TOOL,

	SIM_CIRCUIT,
	VALIDATE_CIRCUIT,
	SIMULATE_CIRCUIT,
	PROBE_CIRCUIT,

	SELECT_BUTTON,

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};


enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_AND2,		//AND gate item in menu
	ITM_OR2,
	ITM_NAND2,
	ITM_NOR2,
	ITM_XOR2,
	ITM_XNOR2,
	ITM_AND32,
	ITM_NOR32,
	ITM_XOR32,
	ITM_BUFF2,
	ITM_NOT2,
	ITM_SWITCH,
	ITM_LED,
	ITM_Connection,
	ITM_sim,
	ITM_EXIT,		//Exit item



	//TODO: Add more items names here


	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum

};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_TRUTH,	//Truth table menu item
	ITM_VALIDATE,
	ITM_PROBE,
	ITM_BACK,
	ITM_EXIT2,

	//TODO:Add more items names here

	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};
enum BottomMenuItem
{
	ITM_UNDO_B,
	ITM_REDO_B,
	ITM_SAVE_B,
	ITM_EDIT_B,
	ITM_delete_B,
	ITM_move_B,
	ITM_import_B,
	ITM_copy_B,
	ITM_paste_B,
	ITM_select_B,
	ITM_cut_B,

	ITM_BTM_CNT
};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5	//Default fan out of 2-input AND gate
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1, y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif

#endif