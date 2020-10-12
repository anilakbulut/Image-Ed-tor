/*ANIL AKBULUT 151044029 PA2*/
/*Libraries I use in my code*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class IMAGE
{
private:
		vector < vector <int> > image_vec; /*two dimensional vector implement*/
		string format;/*stores the format of the file read*/
		int row,column,max;/*variables that store the row, column, and maximum number of pixels in the file.*/  
public:
		int read_image();
		void write_image();
		void Scripts();

		void Menu();
		void print_main_menu();
		void print_read_menu();
		void print_save_menu();
		void print_script_menu();

		int get_row(){ /*Returns the number of row to the user when called.*/
			return row;
		}
		int get_column(){ /*Returns the number of column to the user when called.*/
			return column;
		}
		int get_max(){ /*Returns the number of maximum pixel to the user when called.*/
			return max;
		}
};
int IMAGE::read_image(){ /*This function reads the necessary information for the class object from the file.*/
	const int one_pixel_digit = 3; /*1 pixel equals o 3 digit*/
	string input_filename; /*it stores the file name that the user wants to read.*/
	cin >> input_filename;

	ifstream file(input_filename); /*file opening process */

	int i,j; /*use loops*/
	int x; /*temp variable*/

	if(file.is_open()){ /*if file is open,continue process*/
		getline(file,format); /*stores the format of the file.*/
		file >> row >> column >> max; /*stores the row,column and max variables of the file.*/
		for(i=0;i<row;i++){ /*expands vector by number of rows and columns*/
			for(j=0;j<column*one_pixel_digit;j++)
			{
			    image_vec.push_back(vector <int> ());
            	image_vec[i].push_back(j);
			}
		}
		i=0;
		j=0;
		while(file >> x){ /*stores the remaining pixel values ​​in the file in the vector.*/
			if(j==column*one_pixel_digit){
				j=0;
				i++;
			}
			image_vec[i][j]=x;
			j++;
		}
		file.close();
		return 1;
	}
	else return 0; /*if file is not open return 0 value*/	
}
void IMAGE::write_image(){/*It is the function of writing the pixel values ​​to the file.*/
	string input_filename; /*it stores the file name that the user wants to write.*/
	cin >> input_filename;
	int i,j;/*variables for loops*/

	ofstream file(input_filename); /*file writing process*/

	if(file.is_open()){ /*if file is open,continue*/
		/*write the row,column and max variables of the file.*/
		file << format << endl; 
		file << get_row() << " " << get_column() << endl;
		file << get_max() << endl;
		/*write the pixel variables of the file.*/
		for(i=0;i<get_row();i++){ 
			for(j=0;j<get_column()*3;j++){
				file << image_vec[i][j];
				if(j+1 != get_column()*3) file << " " ;
			}
			if( i + 1 != get_row() ) file << endl;
		}
		file.close();/*file is closed*/
	}
}
void IMAGE::Scripts(){
	const int one_pixel_digit = 3; /*1 pixel equals o 3 digit*/
	float c_r,c_g,c_b; /*coefficient variables to be taken from the user */
	int i,j;/*variables for loops*/
	float count = 0; /*stores the sum of coefficient operations*/
	cin >> c_r ;
	cin >> c_g ;
	cin >> c_b ;
	/*If the coefficients are outside the specified limits, the program fails and closes.*/
	if(c_r>=1 || c_r < 0 || c_g>=1 || c_g < 0 || c_b>=1 || c_b < 0 ) return; 

	/*The required values ​​are collected and reassigned by reading the pixel values ​​three by three.*/
	for(i=0;i<get_row();i++){
		for(j=0;j<get_column()*one_pixel_digit;j = j+3){
			count = image_vec[i][j]*c_r + image_vec[i][j+1]* c_g + image_vec[i][j+2]* c_b;
			if(count > get_max()) count = get_max();
			image_vec[i][j]= count;
			image_vec[i][j+1]= count;
			image_vec[i][j+2]= count;	
		}
	}
}
void IMAGE::print_main_menu(){ /*Contains things to be printed on the screen for the outer menu.*/
	cout << "MAIN MENU" << endl;
	cout << "0 - Exit"  << endl;
	cout << "1 - Open An Image(D)" << endl;
	cout << "2 - Save Image Data(D)" << endl;
	cout << "3 - Scripts(D)" << endl;
}
void IMAGE::print_read_menu(){/*Contains things to be printed on the screen for the inner read menu.*/
	cout << "OPEN AN IMAGE MENU" << endl;
	cout << "0 - UP" << endl;
	cout << "1 - Enter The Name Of The Image File" << endl;
}
void IMAGE::print_save_menu(){/*Contains things to be printed on the screen for the inner save menu.*/
	cout << "SAVE IMAGE DATA MENU" << endl;
	cout << "0 - UP" << endl;
	cout << "1 - Enter A File Name" << endl;
}
void IMAGE::print_script_menu(){/*Contains things to be printed on the screen for the inner convert menu.*/
	cout << "CONVERT TO GRAYSCALE MENU" << endl;
	cout << "0 - UP" << endl;
	cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;
}
void IMAGE::Menu(){
	int button=1,inner_button=1; /*inner and outer's menu variables*/
	while(button!=0){ /*The program continues as long as the button is not 0.*/
		print_main_menu(); /*print on screen outer menu*/
		cin >> button;/*the loop wants from the user for the outer button value each time.*/

		if(button == 1)
			while(inner_button!=0){
				print_read_menu(); /*print on screen inner read menu*/
				cin >> inner_button; /*the loop wants from the user for the inner button value each time.*/
				if(inner_button == 1){
					if(read_image()!=1) return;
				}
			}
		else if(button == 2)
			while(inner_button!=0){
				print_save_menu(); /*print on screen inner save menu*/
				cin >> inner_button;/*the loop wants from the user for the inner button value each time.*/
				if( inner_button == 1) write_image();
			}
			
		else if(button == 3)
			while(inner_button!=0){
				print_script_menu(); /*print on screen inner script menu*/
				cin >> inner_button;/*the loop wants from the user for the inner button value each time.*/
				if(inner_button == 1) Scripts();
			}
		inner_button=1; /*inner button update*/
	}
}
int main()
{
	IMAGE obj; /*An object of the class is created.*/
	obj.Menu(); /*The created object operations are started*/
}