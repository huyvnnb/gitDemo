#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cmath>
//using namespace std;

struct Sinhvien{
    std::string name;
    int age; 
    double math;
    double english;
    double avg;
};
//-----------------------------------
//FUNCTION
bool initFiles(std::fstream &fileIn); //Khởi tạo, mở file
void initData(std::fstream &fileIn, std::vector<Sinhvien>& sv); //Đưa dữ liệu vào Mảng
int getNumberSV(std::vector<Sinhvien>& sv); //Số lượng Sinh Viên
void printSV(std::vector<Sinhvien>& sv); //IN DANH SACH SV
void addSV(std::fstream &fileIn, std::vector<Sinhvien>& listsv);  // THÊM SV
void deleteSV(std::vector<Sinhvien>& sv, int );
void deleteSV(std::fstream &fileIn, std::vector<Sinhvien>& sv, int );
int find(std::vector<Sinhvien>, std::string);
void findSVName(std::vector<Sinhvien> sv);
void syncData(std::fstream &, std::vector<Sinhvien>);
void sortScore(std::vector<Sinhvien>& );
void sortName(std::vector<Sinhvien>& );
void changeInfo(std::vector<Sinhvien>& , int);
float maxAvg(std::vector<Sinhvien>);
void findmaxAvg(std::vector<Sinhvien> );
void indent();
void line();

//--------------------------------------------------
int main(){
    std::fstream fileIn;
    if(!(initFiles(fileIn))){
    	std::cout << "File not exist!" << std::endl;
   		return 0;
    }
    std::vector<Sinhvien> sv;
    initData(fileIn, sv);
    std::cout << "----------------------SINH VIEN ADMINISTRATION-----------------------\n";
    while(true){
	    std::cout << "---------------------------------------------------------------------\n";
	    std::cout << "|     MENU    |\n";
	    std::cout << "---------------------------------------------------------------------\n";
	    std::cout << "1.In danh sach sinh vien\n";
	    std::cout << "2.Them sinh vien\n";
	    std::cout << "3.Xoa sinh vien\n";
	    std::cout << "4.Tim kiem\n";
	    std::cout << "5.Sap xep\n";
	    std::cout << "6.Sua sinh vien\n";
	    std::cout << "7.Tim diem cao nhat\n";
	    std::cout << "8.Xoa man hinh\n";
	    std::cout << "9.Dong bo du lieu\n";
	    std::cout << "10.Thoat chuong trinh\n";

    	int choice;
		std::cout << "Nhap lua chon cua ban: ";
    	std::cin >> choice;
    	std::cin.ignore();
    	switch(choice){
    		case 1:
    			printSV(sv);
    			break;
    		case 2:
    			addSV(fileIn, sv);
    			break;
    		case 3:
    			int delPos;
    			std::cout << "Nhap vi tri muon xoa: ";
    			std::cin >> delPos;
    			deleteSV(fileIn, sv, delPos);
    			break;
    		case 4:
    			int findchoice;
    			std::cout << "---------------------------------------------------------------------\n";
    			std::cout << "1.Tim theo ten\n";
    			std::cout << "2.Tim theo tuoi\n";
    			std::cout << "3.Tim theo diem\n";
    			std::cout << "4.Huy tim kiem\n";
    			std::cout << "---------------------------------------------------------------------\n";
    			std::cout << "Nhap lua chon de tim kiem: "; std::cin>>findchoice;
    			switch(findchoice){
    				case 1:
    					findSVName(sv);
    					break;
    				case 4:	
    					std::cout << "Ket thuc\n";
    					break;
    			}
    			break;
    		case 5:	
    			int sortChoice;
    			std::cout << "1.Theo ten\n";
    			std::cout << "2.Theo diem\n";
    			std::cout << "Nhap lua chon: "; std::cin >> sortChoice;
    			switch(sortChoice){
    				case 1:
    					sortName(sv);
    					break;
    				case 2:
    					sortScore(sv);
    					break;
    			}
    			break;
    		case 6:
    			int changePos;
    			std::cout << "Nhap vi tri thay doi: "; std::cin >> changePos;
    			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    			changeInfo(sv, changePos);
    			break;
    		case 7:
    			findmaxAvg(sv);
    			break;
    		case 8:
    			system("cls");
    			break;
    		case 9:
    			syncData(fileIn, sv);
    			std::cout << "Dong bo thanh cong!" << std::endl;
    			break;

    		case 10:
    			syncData(fileIn, sv);
    			fileIn.close(); 
    			//fileOut.close();
    			return 0;
    	}
    }    
    return 0;
}

//----------------------------------------------------
//Khoi tao file
bool initFiles(std::fstream &fileIn){
	fileIn.open("input.txt", std::ios_base::in | std::ios_base::out | std::ios_base::app);

	if(fileIn.fail()==true){
		return 0;
	}
	return 1;
}

void initData(std::fstream &fileIn, std::vector<Sinhvien> &listSV){
	Sinhvien sv;
	std::string line;
	while(getline(fileIn, line)){
		std::stringstream getInfo(line);
		getline(getInfo, sv.name, '\t');
		getInfo >> sv.age >> sv.math >> sv.english;
		sv.avg = (sv.math + sv.english)/2;
		getInfo >> sv.avg;
		listSV.push_back(sv);
	}
}

int getNumberSV(std::vector<Sinhvien>& sv){
	return sv.size();
}
void indent(){
	std::cout << "          ";
}

void line(){
	std::cout << "+--------------------------------------------------------------------------------+\n";
}

//-------------------------------------------
//IN DANH SÁCH SINH VIÊN
void printSV(std::vector<Sinhvien>& sv){
	int n = sv.size();
	if(n==0){
		std::cout << "No student in list" << std::endl;
		return;
	}
	indent(); line();
	indent();
	std::cout << std::left << "|" << std::setw(10)  << "STT" 
	<< "|" << std::setw(20) << "Name" << "|"
	<< std::right << std::setw(10) << "Age" << "|"
	<< std::setw(10) << "Math" << "|"
	<< std::setw(10) << "English" << "|" 
	<< std::setw(15) << "Average" << "|" <<std::endl;
	indent(); line();
	for(int i=0; i<n; i++){
		indent();
		std::cout << std::left << "|" << std::setw(10) <<  i+1 << "|"
		<< std::setw(20) << sv[i].name << "|"
		<< std::right << std::setw(10) << sv[i].age << "|"
		<< std::setw(10) << sv[i].math << "|"
		<< std::setw(10) << sv[i].english << "|" 
		<< std::setw(15) << sv[i].avg << "|" <<std::endl;
		indent();
		line();
	}
}

//------------------------------------------------
//NHẬP THÊM SINH VIÊN
void addSV(std::fstream &fileIn, std::vector<Sinhvien>& listSV){
	Sinhvien sv;
	std::cout << "-------------------------THEM SINH VIEN--------------------------------\n";
	while(true){
		std::cout << "Name: "; 
		getline(std::cin, sv.name, '\n'); 

		std::cout << "Age: "; 
		std::cin >> sv.age; 
		//std::cin.ignore(30,'\n');

		std::cout << "Math: "; 
		std::cin >> sv.math; 

		std::cout << "English: "; 
		std::cin >> sv.english; 

		fileIn.close();
		fileIn.open("input.txt", std::ios_base::out | std::ios_base::app);

		fileIn << sv.name << '\t' << sv.age << '\t' << sv.math << '\t' << sv.english << '\n';

		sv.avg = (sv.english + sv.math)/2;
		listSV.push_back(sv);
		if (fileIn.good()) {
        	std::cout << "The file is open and ready for input/output operations." << std::endl;
        	fileIn.flush();
    	} else {
        	std::cerr << "An error occurred when opening the file." << std::endl;
    	}

		std::cout << "----MORE STUDENT? \n1: CONTINUE \n0: EXIT----\n";
		int programEnd;
		std::cin >> programEnd;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if(programEnd==0){
			std::cout << "FINISH!\n";
			std::cout << "------------------------------------------------------------------" << std::endl;
			break;
		}
		else if(programEnd==1){
			continue;
		}
		else{
			std::cout << "Khong hop le, dung chuong trinh\n";
			break;
		}
	}
}

void deleteSV(std::fstream &fileIn, std::vector<Sinhvien> &sv, int pos){
	sv.erase(sv.begin()+pos-1);
}

int find(std::string str, std::string substr){
	int n = str.size();
	int m = substr.size();
	if(m>n){
		return 0;
	}
	for(int i=0; i<=n-m; i++){
		int j;
		for(j=0; j<m; j++){
			if(str[i+j] != substr[j]){
				break;
			}
		}
		if(j==m){
			return 1;
		}
	}
	return 0;
}

void findSVName(std::vector<Sinhvien> sv){
	std::string findName;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//std::cin.ignore(100, '\n');
	std::cout << "Nhap ten muon tim: "; getline(std::cin, findName);
	std::cout << std::endl;
	int n = sv.size();
	int stt = 0;
	std::cout << "------------------------TIM KIEM SINH VIEN-------------------------\n";
	indent(); line();
	indent();
	std::cout << std::left << "|" << std::setw(10)  << "STT" 
	<< "|" << std::setw(20) << "Name" << "|"
	<< std::right << std::setw(10) << "Age" << "|"
	<< std::setw(10) << "Math" << "|"
	<< std::setw(10) << "English" << "|" 
	<< std::setw(15) << "Average" << "|" <<std::endl;
	indent(); line();
	for(int i=0; i<n; i++){
		if(find(sv[i].name, findName) == 1){
			stt++;
			indent();
		std::cout << std::left << "|" << std::setw(10) <<  i+1 << "|"
		<< std::setw(20) << sv[i].name << "|"
		<< std::right << std::setw(10) << sv[i].age << "|"
		<< std::setw(10) << sv[i].math << "|"
		<< std::setw(10) << sv[i].english << "|" 
		<< std::setw(15) << sv[i].avg << "|" <<std::endl;
		indent();
		line();
		}
	}
	if(stt==0){
		std::cout << "Khong tim thay sinh vien nao\n";
	}
}

void syncData(std::fstream &fileIn, std::vector<Sinhvien> sv){
	fileIn.close();
	fileIn.open("input.txt", std::ios_base::out);
	int n = sv.size();
	for(int i=0; i<n; i++){
		fileIn << sv[i].name << '\t' << sv[i].age << '\t' << sv[i].math << '\t' << sv[i].english << '\t' << sv[i].avg << "\n";
	}
}

void sortScore(std::vector<Sinhvien>& sv){
	int n = sv.size();
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(sv[i].avg < sv[j].avg){
				Sinhvien temp = sv[i];
				sv[i] = sv[j];
				sv[j] = temp;
			}
		}
	}
}	

void sortName(std::vector<Sinhvien>& sv){
	int n = sv.size();
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(sv[i].name > sv[j].name){
				Sinhvien temp = sv[i];
				sv[i] = sv[j];
				sv[j] = temp;
			}
		}
	}
}	

void changeInfo(std::vector<Sinhvien>& sv, int pos){
	pos--;
	std::cout << "Nhap ten moi: "; getline(std::cin, sv[pos].name, '\n');
	std::cout << "Nhap tuoi: "; std::cin >> sv[pos].age;
	std::cout << "Nhap diem Toan: "; std::cin >> sv[pos].math;
	std::cout << "Nhap diem Anh: "; std::cin >> sv[pos].english;
	sv[pos].avg = (sv[pos].math + sv[pos].english)/2;
}

float maxAvg(std::vector<Sinhvien> sv){
	float max = sv[0].avg;
	int n = sv.size();
	for(int i=1; i<n; i++){
		if(sv[i].avg > max){
			max = sv[i].avg;
		}
	}
	return max;
}

void findmaxAvg(std::vector<Sinhvien> sv){
	float max = maxAvg(sv);
	int n = sv.size();
	int stt = 0;
	std::cout << "-------------------------DIEM CAO NHAT---------------------------\n";
	indent(); line();
	indent();
	std::cout << std::left << "|" << std::setw(10)  << "STT" 
	<< "|" << std::setw(20) << "Name" << "|"
	<< std::right << std::setw(10) << "Age" << "|"
	<< std::setw(10) << "Math" << "|"
	<< std::setw(10) << "English" << "|" 
	<< std::setw(15) << "Average" << "|" <<std::endl;
	indent(); line();
	for(int i=0; i<n; i++){
		if(sv[i].avg == max){
			stt++;
			indent();
		std::cout << std::left << "|" << std::setw(10) <<  i+1 << "|"
		<< std::setw(20) << sv[i].name << "|"
		<< std::right << std::setw(10) << sv[i].age << "|"
		<< std::setw(10) << sv[i].math << "|"
		<< std::setw(10) << sv[i].english << "|" 
		<< std::setw(15) << sv[i].avg << "|" <<std::endl;
		indent();
		line();
		}
	}
	if(stt==0){
		std::cout << "Khong tim thay hoc sinh nao!\n";
	}
}
