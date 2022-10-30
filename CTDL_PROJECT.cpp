#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_set>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<vector>
using namespace std;


const int lightGreen = 10;
const int aqua = 3;
const string soDuBanDau = "50000";
const string donViTienTe = "VND";
const int nhapSai = 3;

void Dang_Nhap();
void get_time(string& _time);

template<typename var> class User
{
private:
    var user_name;
    var password;
    int nhap_sai = 0;

    void appen(User** head, var usn, var pin)
    {
        if ((*head) == NULL)
        {
            (*head) = new User(usn, pin, NULL);
            return;
        }
        else {
            User* last = (*head);
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = new User(usn, pin, NULL);
        }
    }

    void take_input_password(var& password)
    {
        while (true)
        {
            char c = _getch();
            if (c == 13)
            {
                break;
            }
            else if (c == '\b' && password.length() > 0)
            {
                password.pop_back();
                cout << "\b \b";
            }
            else
            {
                password.push_back(c);
                cout << "*";
            }
        }

    }
    void menu_user(User* user, User* head)
    {
        system("cls");
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "\t\t\t\t\t*****************MENU*****************" << endl;
        SetConsoleTextAttribute(hStdOut, lightGreen);
        cout << "\t\t\t\t\t\t1.Xem thong tin tai khoan" << endl;
        cout << "\t\t\t\t\t\t2.Rut tien" << endl;
        cout << "\t\t\t\t\t\t3.Chuyen tien" << endl;
        cout << "\t\t\t\t\t\t4.Xem noi dung giao dich" << endl;
        cout << "\t\t\t\t\t\t5.Doi ma pin" << endl;
        cout << "\t\t\t\t\t\t6.Thoat" << endl;
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "\t\t\t\t\t**************************************" << endl;
        SetConsoleTextAttribute(hStdOut, lightGreen);
        cout << "\t\t\t\t\t\t-->";
        int chose; cin >> chose;
        switch (chose)
        {
        case 1:
            user->xem_thong_tin_tai_khoan(user, head);
        case 2:
            user->rut_tien(user, head);
        case 3:
            user->chuyen_tien(user, head);
        case 4:
            user->xem_noi_dung_giao_dich(user, head);
        case 5:
            user->doi_mat_khau(user, head);
        case 6:
            head->delete_user_list(&head);
            ::Dang_Nhap();
        default:
            head->delete_user_list(&head);
            ::Dang_Nhap();
        }
    }
    void xem_thong_tin_tai_khoan(User* user, User* head)
    {
        ifstream myfile;
        myfile.open(user->user_name + ".txt", ios::in);
        var output = "";
        cout << "ID: "; getline(myfile, output); cout << output << endl;
        cout << "Ho ten: "; getline(myfile, output); cout << output << endl;
        cout << "So du: "; getline(myfile, output); cout << output << endl;
        cout << "Dvtt: "; getline(myfile, output); cout << output << endl;
        myfile.close();
        system("pause");
        user->menu_user(user, head);
    }
    void rut_tien(User* user, User* head)
    {
        fstream myfile;
        myfile.open(user->user_name + ".txt", ios::in);
        var id = "", name = "", money = "", dvtt = "";
        getline(myfile, id);
        getline(myfile, name);
        getline(myfile, money);
        getline(myfile, dvtt);
        if (stoi(money) < 100000)
        {
            cout << "So du khong du de rut tien (duoi 100000)" << endl;
            myfile.close();
            system("pause");
            user->menu_user(user, head);
        }
        cout << "So du hien tai: " << money << endl;
        cout << "Nhap so tien can rut (\"0\" = Thoat):  "; int rut; cin >> rut;
        if (rut == 0)
        {
            user->menu_user(user, head);
        }
        while (rut < 50000 || rut % 50000 != 0 || rut > stoi(money) - 50000)
        {
            cout << "So tien can rut phai lon hon 50000, la boi cua 50000 va duoi " << stoi(money) - 50000 << "!" << endl;
            cout << "Nhap lai so tien can rut (0:exit): "; cin >> rut;
            if (rut == 0)
            {
                user->menu_user(user, head);
            }
        }
        myfile.close();
        money = to_string(stoi(money) - rut);
        cout << "Rut thanh cong so tien " << rut << "VND" << endl;
        myfile.open(user->user_name + ".txt", ios::out);
        myfile << id << endl << name << endl << money << endl << dvtt;
        myfile.close();
        myfile.open("LichSu" + user->user_name + ".txt", ios::app);

        //get time
        var time; ::get_time(time);

        myfile << id << "#" << "rut" << "#" << rut << "#" << time;
        myfile.close();
        system("pause");
        user->menu_user(user, head);
    }
    void chuyen_tien(User* user, User* head)
    {
        fstream source_file;
        source_file.open(user->user_name + ".txt", ios::in);
        var id = "", name = "", sdkd = "", dvtt = "", tkth = "";
        getline(source_file, id);
        getline(source_file, name);
        getline(source_file, sdkd);
        getline(source_file, dvtt);
        source_file.close();

        if (stoi(sdkd) < 100000)
        {
            cout << "So du tai khoan khong du" << endl;
            system("pause");
            user->menu_user(user, head);
        }
        else {
            cout << "So du kha dung: " << sdkd << endl;
            cout << "Tai khoan thu huong (\"0\" = Thoat): "; getline(cin >> ws, tkth);
            if (tkth == "0")
            {
                user->menu_user(user, head);
            }
            while (tkth.length() != 14 || tkth == user->user_name)
            {
                cout << "Tai khoan thu huong bao gom 14 chu so va khong duoc chuyen cho chinh minh, vui long nhap lai (0:exit): "; getline(cin >> ws, tkth);
                if (tkth == "0")
                {
                    user->menu_user(user, head);
                }
            }
            User* check = head;
            while (check != NULL)
            {
                if (check->user_name == tkth)
                {
                    fstream des_file;
                    des_file.open(check->user_name + ".txt", ios::in);
                    var _id = "", _name = "", _sdkd = "", _dvtt = "", transmon = "";
                    getline(des_file, _id);
                    getline(des_file, _name);
                    getline(des_file, _sdkd);
                    getline(des_file, _dvtt);
                    des_file.close();

                    cout << "Tai khoan thu huong: " << _id << endl;
                    cout << "Ten tkth: " << _name << endl;
                    cout << "Nhap so tien can chuyen: "; getline(cin >> ws, transmon);

                    while (stoi(transmon) < 50000 || stoi(transmon) % 50000 != 0 || stoi(transmon) > stoi(sdkd) - 50000)
                    {
                        cout << "So tien can chuyen phai lon hon 50000, boi cua 50000 va duoi " << stoi(sdkd) - 50000 << " nhap lai: ";
                        getline(cin >> ws, transmon);
                    }
                    //chuyen
                    sdkd = to_string(stoi(sdkd) - stoi(transmon));
                    //nhan
                    _sdkd = to_string(stoi(_sdkd) + stoi(transmon));

                    //update ID.txt
                    source_file.open(user->user_name + ".txt", ios::out);
                    source_file << id << endl << name << endl << sdkd << endl << dvtt << endl;
                    source_file.close();

                    des_file.open(check->user_name + ".txt", ios::out);
                    des_file << _id << endl << _name << endl << _sdkd << endl << _dvtt << endl;
                    des_file.close();

                    var time;
                    ::get_time(time);
                    cout << "Chuyen thanh cong so tien " << transmon << " cho tk: " << _id << " thoi gian: " << time << endl;

                    //update Lichsu.txt
                    source_file.open("LichSu" + user->user_name + ".txt", ios::app);
                    source_file << id << "#" << "chuyen" << "#" << transmon << "#" << time;
                    source_file.close();

                    des_file.open("LichSu" + check->user_name + ".txt", ios::app);
                    des_file << _id << "#" << "nhan" << "#" << transmon << "#" << time;
                    des_file.close();
                    system("pause");
                    user->menu_user(user, head);
                }
                check = check->next;
            }
            cout << "Khong tim thay ten tai khoan, vui long thu lai" << endl;
            source_file.close();
            user->chuyen_tien(user, head);
        }
    }
    void xem_noi_dung_giao_dich(User* user, User* head)
    {
        ifstream myfile;
        myfile.open("LichSu" + user->user_name + ".txt", ios::in);
        var lichsu = "", sub = "";
        char sep = '#';
        while (getline(myfile, lichsu) && lichsu.length() != 0)
        {
            vector<var> ls;
            stringstream stream_data(lichsu);
            while (getline(stream_data, sub, sep))
            {
                ls.push_back(sub);
            }
            cout << ls.at(1) << " " << ls.at(2) << " " << ls.at(3) << endl;
        }
        system("pause");
        user->menu_user(user, head);
    }
    void doi_mat_khau(User* user, User* head)
    {
        var mkm;
        var nlmkm;
        cout << "Nhap mat khau moi (exit:0): "; user->take_input_password(mkm);
        if (mkm == "0")
        {
            user->menu_user(user, head);
        }
        cout << endl;
        while (mkm.length() != 6 || mkm == user->password || mkm == "123456" || mkm == "111111")
        {
            mkm = "";
            cout << "Mat khau phai gom 6 chu so, khac mat khau cu, vui long thu lai (exit:0): "; user->take_input_password(mkm);
            if (mkm == "0")
            {
                user->menu_user(user, head);
            }
            cout << endl;
        }

        cout << "Nhap lai mat khau moi: "; user->take_input_password(nlmkm);
        cout << endl;
        if (mkm != nlmkm)
        {
            cout << "Mat khau khong duoc trung khop, vui long thu lai!" << endl;
            user->doi_mat_khau(user, head);
        }
        else {
            user->password = mkm;
            cout << "Doi mat khau thanh cong!" << endl;
            system("pause");
            head->update_file_the_tu(head);
            user->menu_user(user, head);
            return;
        }
    }



    /////////////////////////////////////////Public User///////////////////////////////////////////////////    
public:


    User(var usn, var pin, User* next) :user_name(usn), password(pin), next(next), nhap_sai(0) {}
    User():user_name(""),password(""),next(NULL),nhap_sai(0) {}

    User<var>* next;
    var get_user_name() { return this->user_name; }

    void update_file_the_tu(User* head)
    {
        if (head == NULL)
        {
            cout << "Khong co du lieu de update file TheTu.txt" << endl;
            return;
        }
        fstream myfile;
        myfile.open("TheTu.txt", ios::out);
        while (head != NULL)
        {
            myfile << head->user_name << endl << head->password << endl;
            head = head->next;
        }
        myfile.close();
    }

    void delete_user_list(User** head)
    {
        while ((*head) != NULL)
        {
            User* del = (*head);
            (*head) = (*head)->next;
            delete(del);
        }
    }

    void read_file_the_tu(User** head)
    {
        ifstream myfile;
        myfile.open("TheTu.txt", ios::in);
        var usn = "", pin = "";
        while (myfile >> usn >> pin)
        {
            (*head)->appen(&(*head), usn, pin);
        }
        myfile.close();
    }

    void dang_nhap_user(User* head)
    {
        system("cls");
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "\t\t\t\t\t**********************************" << endl
            << "\t\t\t\t\t*                                *" << endl
            << "\t\t\t\t\t*";
        SetConsoleTextAttribute(hStdOut, lightGreen);
        cout << "         DANG NHAP USER         ";
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "*" << endl
            << "\t\t\t\t\t*                                *" << endl
            << "\t\t\t\t\t**********************************" << endl;

        var usn = ""; var pin = "";
        SetConsoleTextAttribute(hStdOut, lightGreen);


        cout << "\t\t\t\t\tUser (exit:0):"; getline(cin >> ws, usn);


        if (usn == "0")
        {
            head->delete_user_list(&head);
            ::Dang_Nhap();
        }

        if (usn.length() != 14)
        {
            cout << endl;
            cout << "Tai khoan phai gom 14 chu so,vui long thu lai" << endl;
            system("pause");
            head->dang_nhap_user(head);
        }
        fstream myfile;
        myfile.open("Freezed_id.txt", ios::in);
        var str = "";
        while (getline(myfile, str))
        {
            if (str == usn)
            {
                cout << endl;
                cout << "Tai khoan cua ban da bi khoa do nhap sai qua 3 lan, lien he admin de mo khoa !" << endl;
                myfile.close();
                system("pause");
                head->dang_nhap_user(head);
            }
        }
        myfile.close();
        cout << "\t\t\t\t\tPin  :\t"; head->take_input_password(pin);


        User* user = head;
        while (user != NULL)
        {
            while (user->user_name == usn && user->password != pin)
            {
                user->nhap_sai += 1;
                if (user->nhap_sai >= 3)
                {
                    myfile.open("Freezed_id.txt", ios::app);
                    myfile << usn << endl;
                    myfile.close();
                    cout << endl;
                    cout << "Tai khoan cua ban da bi khoa do nhap sai qua 3 lan, lien he admin de mo khoa !" << endl;
                    system("pause");
                    head->dang_nhap_user(head);
                }
                cout << endl;
                cout << "Sai ma pin, ban con " << nhapSai - user->nhap_sai << " lan thu: ";
                pin = "";
                head->take_input_password(pin);
            }
            if (user->user_name == usn && user->password == pin)
            {
                user->nhap_sai = 0;
                if (user->password == "123456")
                {
                    cout << endl;
                    cout << "Day la lan dau tien ban dang nhap, vui long doi mat khau!" << endl;
                    user->doi_mat_khau(user, head);
                    head->update_file_the_tu(head);
                    return;
                }
                else {
                    user->menu_user(user, head);
                    return;
                }
            }
            user = user->next;
        }
        head->dang_nhap_user(head);
    }
};
/////////////////////////////////////////Class Admin/////////////////////////////////////////////

template <typename var> class Admin : private  User<string>
{
private:
    var user_name;
    var password;
    Admin<var>* next;
    void push_front(Admin** head, var usn, var pin)
    {
        (*head) = new Admin(usn, pin, (*head));
    }

    void print_admin(Admin* head)
    {
        while (head != NULL)
        {
            cout << head->user_name << " " << head->password;
            cout << endl;
            head = head->next;
        }
    }

    void take_input_password(var& password)
    {
        while (true)
        {
            char c = _getch();
            if (c == 13)
            {
                break;
            }
            else if (c == '\b' && password.length() > 0)
            {
                password.pop_back();
                cout << "\b \b";
            }
            else
            {
                password.push_back(c);
                cout << "*";
            }
        }
    }
    void menu_admin(Admin* user, Admin* head)
    {
        system("cls");
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "\t\t\t\t\t*****************MENU*****************" << endl;
        SetConsoleTextAttribute(hStdOut, lightGreen);
        cout << "\t\t\t\t\t\t1.Xem danh sach tai khoan" << endl;
        cout << "\t\t\t\t\t\t2.Them tai khoan" << endl;
        cout << "\t\t\t\t\t\t3.Xoa tai khoan" << endl;
        cout << "\t\t\t\t\t\t4.Mo tai khoan" << endl;
        cout << "\t\t\t\t\t\t5.Thoat" << endl;
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "\t\t\t\t\t**************************************" << endl;
        SetConsoleTextAttribute(hStdOut, lightGreen);
        cout << "\t\t\t\t\t\t-->";
        int chose; cin >> chose;
        switch (chose)
        {
        case 1:
            user->xem_danh_sach_tai_khoan(user, head);
        case 2:
            user->them_tai_khoan(user, head);
        case 3:
            user->xoa_tai_khoan(user, head);
        case 4:
            user->mo_khoa_tai_khoan(user, head);
        case 5:
            head->delete_admin_list(&head);
            ::Dang_Nhap();
        default:
            head->delete_admin_list(&head);
            ::Dang_Nhap();
        }
    }
    void delete_admin_list(Admin** head)
    {
        while ((*head) != NULL)
        {
            Admin* del = (*head);
            (*head) = (*head)->next;
            delete (del);
        }
    }
    void print_spaces(int spaces)
    {
        for (int i = 0; i < spaces; i++)
        {
            cout << " ";
        }
    }
    void xem_danh_sach_tai_khoan(Admin* user, Admin* head)
    {
        ifstream myfile;
        ifstream myidfile;
        myfile.open("TheTu.txt", ios::in);
        cout << "Danh sach thong tin tai khoan" << endl;
        var tk = "", mk = "", ht = "", sd = "", dvtt = "", dump ="";
        int count = 1;
        while (myfile >> tk >> mk)
        {
            myidfile.open(tk + ".txt", ios::in);
            getline(myidfile, dump);
            getline(myidfile, ht);
            getline(myidfile, sd);
            getline(myidfile, dvtt);
            if (count <= 9)
            {
                cout << 0;
            }
            cout << count << ".TK:" << tk << "\tMK:" << mk << "\t" << ht;
            user->print_spaces(30 - int(ht.length()));
            cout << sd;
            user->print_spaces(10 - int(sd.length()));
            cout << dvtt << endl;
            myidfile.close();
            count++;
        }
        myfile.close();
        system("pause");
        user->menu_admin(user, head);
    }
    void them_tai_khoan(Admin* user, Admin* head)
    {
        fstream myfile;
        myfile.open("TheTu.txt", ios::in);
        unordered_set<var> dstk;
        var tk = "", mk = "";
        while (myfile >> tk >> mk)
        {
            dstk.insert(tk);
        }
        myfile.close();
        myfile.open("TheTu.txt", ios::app);
        cout << "Nhap ID tai khoan moi: "; getline(cin >> ws, tk);
        while (tk.length() != 14 || dstk.find(tk) != dstk.end())
        {
            cout << "ID tai khoan phai gom 14 chu so va khac tai khoan da ton tai, nhap lai ID: "; getline(cin >> ws, tk);
        }
        //Them vao file TheTu.txt
        myfile << tk << endl << "123456" << endl;
        myfile.close();

        //them thong tin vao file id.txt
        myfile.open(tk + ".txt", ios::app);
        myfile << tk << endl;
        cout << "Ho ten chu so huu: "; var name = ""; getline(cin >> ws, name);
        myfile << name << endl << soDuBanDau << endl << donViTienTe << endl;
        myfile.close();
        myfile.open("LichSu" + tk + ".txt", ios::app);
        myfile.close();
        cout << "Them thanh cong tai khoan " << tk << " mat khau mac dinh la 123456" << endl;
        system("pause");
        user->menu_admin(user, head);
    }
    void xoa_tai_khoan(Admin* heada, Admin* head)
    {
        User<var>* user_list = NULL;
        user_list->read_file_the_tu(&user_list);
        var id = "";

        while (true)
        {
            cout << "Nhap ID tai khoan can xoa (exit:0): "; getline(cin >> ws, id);
            if (id == "0")
            {
                head->menu_admin(heada, head);
            }
            while (id.length() != 14)
            {
                cout << "ID tai khoan phai bao gom 14 chu so, nhap lai (exit:0): "; getline(cin >> ws, id);
            }
            User<var>* headu = user_list;
            User<var>* preu = user_list;
            bool flag = false;
            while (headu != NULL)
            {
                if (headu->get_user_name() == id)
                {
                    preu->next = headu->next;
                    User<var>* del = headu;
                    //if del is in head
                    if (del == user_list)
                    {
                        user_list = user_list->next;
                    }
                    delete(del);
                    flag = true;
                    cout << "Xoa thanh cong tai khoan " << id << endl;
                    user_list->update_file_the_tu(user_list);
                    remove((id + ".txt").c_str());
                    remove(("LichSu" + id + ".txt").c_str());
                    break;
                }
                preu = headu;
                headu = headu->next;
            }
            if (!flag)
            {
                cout << "Khong tim thay id can xoa, vui long thu lai" << endl;
            }
            else {
                break;
            }
        }
        user_list->delete_user_list(&user_list);
        system("pause");
        head->menu_admin(heada, head);
    }

    void mo_khoa_tai_khoan(Admin* user, Admin* head)
    {
        cout << "Nhap tai khoan can mo khoa (exit:0): ";
        var unlock = ""; getline(cin >> ws, unlock);
        if (unlock == "0")
        {
            user->menu_admin(user, head);
        }
        fstream myfile;
        myfile.open("Freezed_id.txt", ios::in);
        unordered_set<var>set;
        var to_set = "";
        while (getline(myfile, to_set))
        {
            set.insert(to_set);
        }
        myfile.close();
        bool flag = false;

        if (set.find(unlock) != set.end())
        {
            flag = true;
        }
        if (flag)
        {
            set.erase(set.find(unlock));
            myfile.open("Freezed_id.txt", ios::out);
            myfile.clear();
            for (auto& str : set)
            {
                myfile << str << endl;
            }
            myfile.close();
            cout << "Mo khoa thanh cong tai khoan " << unlock << endl;
            system("pause");
            head->menu_admin(user, head);
        }
        else {
            cout << "Khong tim thay tai khoan can mo khoa, vui long thu lai!" << endl;
            system("pause");
            user->menu_admin(user, head);
        }
    }

    //////////////////////////////public//////////////////////////////////////////
public:
    Admin(var usn, var pin, Admin* next) :user_name(usn), password(pin), next(next) {}
    void dang_nhap_admin(Admin* head)
    {
        system("cls");
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "\t\t\t\t\t**********************************" << endl
            << "\t\t\t\t\t*                                *" << endl
            << "\t\t\t\t\t*";
        SetConsoleTextAttribute(hStdOut, lightGreen);
        cout << "         DANG NHAP ADMIN        ";
        SetConsoleTextAttribute(hStdOut, aqua);
        cout << "*" << endl
            << "\t\t\t\t\t*                                *" << endl
            << "\t\t\t\t\t**********************************" << endl;

        var usn = ""; var pin = "";
        SetConsoleTextAttribute(hStdOut, lightGreen);
        cout << "\t\t\t\t\tUser (0:exit) :\t"; getline(cin >> ws, usn);

        if (usn == "0")
        {
            head->delete_admin_list(&head);
            ::Dang_Nhap();
        }
        cout << "\t\t\t\t\tPin  :\t"; head->take_input_password(pin);

        Admin* admin = head;
        while (admin != NULL)
        {
            if (usn == admin->user_name && pin == admin->password)
            {
                admin->menu_admin(admin, head);
                return;
            }
            admin = admin->next;
        }
        system("cls");
        head->dang_nhap_admin(head);
    }

    void read_file(Admin** admin)
    {
        ifstream myfile;
        myfile.open("Admin.txt", ios::in);
        var usn = "", pin = "";
        while (myfile >> usn >> pin)
        {
            (*admin)->push_front(&(*admin), usn, pin);
        }
        myfile.close();
    }
};

void get_time(string& _time)
{
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    _time = asctime(timeinfo);

}
void Dang_Nhap()
{
    system("cls");
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, aqua);
    cout << "\t\t\t\t\t*************";
    SetConsoleTextAttribute(hStdOut, lightGreen);
    cout << "DANG NHAP";
    SetConsoleTextAttribute(hStdOut, aqua);
    cout << "*************" << endl;
    SetConsoleTextAttribute(hStdOut, lightGreen);
    cout << "\t\t\t\t\t\t1.Dang nhap Admin" << endl;
    cout << "\t\t\t\t\t\t2.Dang nhap User" << endl;
    cout << "\t\t\t\t\t\t3.Thoat" << endl;
    cout << "\t\t\t\t\t\t-->"; int chose; cin >> chose;
    SetConsoleTextAttribute(hStdOut, aqua);

    if (chose == 1)
    {
        Admin<string>* admin = NULL;
        admin->read_file(&admin);
        admin->dang_nhap_admin(admin);
    }
    else if (chose == 2) {
        User<string>* user = NULL;
        user->read_file_the_tu(&user);
        user->dang_nhap_user(user);
    }
    else {
        exit(0);
    }
}
int main()
{
    Dang_Nhap();
}
