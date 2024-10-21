#include<bits/stdc++.h>
//#include<matlabcpp.h>
//#include "matlabcppinterface.h" 
using namespace std;

class UNICODE_UTF8 {
    private:
        vector < char > utf8_table;
    public:
        UNICODE_UTF8();
        void display_utf8_table();
        uint8_t select_character(unsigned int);
        vector<vector<unsigned int>> decimal_to_binary_uint_8(const vector<uint8_t>& decimals);
        vector<unsigned int> binary_to_decimal(const vector<vector<unsigned int>> binarys);
};

// Hàm thêm bảng mã UTF_8 
UNICODE_UTF8 :: UNICODE_UTF8(){

    // Tao bang ma UTF-8 tu 0 - 255 (8 bit)
    for ( int i = 0; i < 256; i ++){
        utf8_table.push_back(static_cast<char> (i));
    }
}

// Hàm hiện ra màn hinh bảng mã UTF_8
void UNICODE_UTF8 :: display_utf8_table(){

    // Xuat ra man bang ma UTF-8
    cout << "Bang ma UTF-8( 8 bit): " << endl;
    for ( int i = 0; i < 256; i ++){
        cout << "Thap phan: " << i << " - Ky tu: " << utf8_table[i] << endl;
    }
}

// Hàm lấy dữ liệu là số thập phân từ người dùng
uint8_t UNICODE_UTF8 :: select_character(unsigned int decimal_number){
    
    // Cho ki tu dua tren so thap phan tu 0 - 255
    while (decimal_number > 255){ // bỏ qua bước kiểm tra decimal_number < 0 vì uint8_t luôn lớn hơn 0
        cout << "So da nhap khong nam trong pham vi 0 - 255, vui long nhap lai: ";
        cin >> decimal_number;
    }
    return static_cast<uint8_t>(decimal_number); // chuyển về kiểu dữ liệu uint8_t 

}

// Hàm chuyển từ số thập phân về nhị phân dưới dạng một ma trận (Sử dụng thuật toán chuyển đổi)
vector<vector<unsigned int>> UNICODE_UTF8::decimal_to_binary_uint_8(const vector<uint8_t>& decimals){
    vector<vector <unsigned int>> binary_matrix;
    for (uint8_t dec : decimals){
        vector < unsigned int > binary_row(8, 0); // Tạo một hàng có 8 bit, khởi tạo tất cả bằng 0
        int index = 7; // Lưu vào vector theo thứ tự ngược với 
        while (dec > 0 && index >= 0){
            binary_row[index] = dec % 2;
            dec = dec / 2;
            index --;
        }
        binary_matrix.push_back(binary_row);
    }
    return binary_matrix;
}

// Hàm chuyển từ số dạng nhị phân sang thập phân dưới dạng một ma trận (Sử dụng thuật toán chuyển đổi)
vector<unsigned int> UNICODE_UTF8::binary_to_decimal(const vector<vector<unsigned int>> binarys) {
    vector<unsigned int> decimals; // Chỉ cần sử dụng vector 1 chiều
    for (const auto &row : binarys) {
        unsigned int decimal_value = 0;
        for (int i = 0; i < row.size(); i++) {
            decimal_value += row[i] * pow(2, 7 - i);
        }
        decimals.push_back(decimal_value); // Thêm giá trị thập phân vào vector 1 chiều
    }
    return decimals; // Trả về vector chứa các giá trị thập phân
}



class BCC {
    private:
        vector<vector<unsigned int>> matrix;

    public:
        BCC(const vector<vector<unsigned int>>& input_matrix);
        vector<vector<unsigned int>> xor_matrix();
        vector <float> calculate(float, float, float);
        vector<float> detect_voltage_ranges(float ,float ,float );
        vector<unsigned int> voltages_to_bits(const vector<float>& );
        bool check_error(const vector<vector<unsigned int>>& );
        void correct_error(vector<vector<unsigned int>>& );
        void display_matrix_without_bcc();
        
};
/*Các hàm chuyển từ mã UNUICODE_UTF8 thành chuỗi bit */
// Constructor
BCC::BCC(const vector<vector<unsigned int>>& input_matrix) {
    matrix = input_matrix;
}

// Phương thức tính phép XOR và thêm vào cuối mỗi hàng
vector<vector<unsigned int>> BCC::xor_matrix() {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Thêm cột XOR vào mỗi hàng
    for (int i = 0; i < rows; i++) {
        unsigned int xor_result = 0;
        for (int j = 0; j < cols; j++) {
            xor_result ^= matrix[i][j];  // Thực hiện phép XOR
        }
        matrix[i].push_back(xor_result);  // Thêm kết quả vào cuối hàng
    }

    // Tính toán XOR cho từng cột
    vector<unsigned int> column_xor(cols + 1, 0); // Khởi tạo vector chứa kết quả XOR cho từng cột
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            column_xor[j] ^= matrix[i][j];  // Thực hiện phép XOR cho từng cột
        }
    }

    // Đảo bit cho hàng kết quả XOR
    for (int j = 0; j < cols + 1; j++) {
        column_xor[j] = column_xor[j] == 0 ? 1 : 0;  // Đổi bit 0 thành 1 và 1 thành 0
    }

    // Thêm hàng chứa kết quả XOR đã đổi bit vào cuối ma trận
    matrix.push_back(column_xor); 

    return matrix; 
}

/* Các hàm để chuyển từ đường truyền, các chuỗi điện áp thành bit 0, 1*/
// Hàm tính toán các thông số
vector <float> BCC :: calculate( float U1, float U2, float U3){
    vector < float > vtr; 
    // Tính mức điện áp phân biệt giữa hai tín hiệu
    float Delta_U12 = ( U1 + U2 ) / 2;
    vtr.push_back(Delta_U12);
    float Delta_U23 = ( U2 + U3 ) / 2;
    vtr.push_back(Delta_U23);

    // Tính dải điện áp bên nhận sẽ tương thích với tín hiệu bên gửi
    float Delta_Up = abs(U1 - U2) / 2;
    vtr.push_back(Delta_Up);

    float SNRmin = 6.02;
    vtr.push_back(SNRmin);

    float Nmax = 0;
    Nmax = min( abs( U1 - U2 ), abs( U2 - U3)) / 2;
    vtr.push_back(Nmax);
    
    return vtr;
}

//
vector<float> BCC::detect_voltage_ranges(float U1, float U2, float U3) {
    vector<float> volt(6); // Vector chứa dải điện áp
    float voltages[3] = {U1, U2, U3};
    float Nmax = min(abs(U1 - U2), abs(U2 - U3)) / 2;

    // Tính toán dải điện áp cho từng mức
    for (int i = 0; i < 3; i++) {
        volt[i * 2] = voltages[i] - Nmax;  // Dải thấp nhất
        volt[i * 2 + 1] = voltages[i] + Nmax;  // Dải cao nhất
        
        // Kiểm tra xem dải điện áp có chứa giá trị của voltages[i] không
        if (volt[i * 2] <= voltages[i] && volt[i * 2 + 1] >= voltages[i]) {
            // Nếu chứa, có thể thực hiện thêm xử lý ở đây
            cout << "Dai dien ap cho U" << (i + 1) << " chua " << voltages[i] << endl;
        } else {
            cout << "Dai dien ap cho U" << (i + 1) << " khong chua " << voltages[i] << endl;
        }
    }

    return volt; // Trả về vector chứa các dải điện áp
}



// Hàm chuyển từ 3 mức điện áp cao, trung bình, thấp về các bit 0 và 1
vector<unsigned int> BCC::voltages_to_bits(const vector<float>& voltages) {
    vector<unsigned int> bits;
    
    for (float voltage : voltages) {
        if (voltage > 1.5) { // Cao nhất
            bits.push_back(1);
        } else if (voltage >= 0.5 && voltage <= 1.5) { // Trung bình
            bits.push_back(0);
        } else { // Thấp nhất
            bits.push_back(0);
        }
    }
    
    return bits;
}

// Hàm kiểm tra lỗi dựa vào mã kiểm soát lỗi BCC
bool BCC::check_error(const vector<vector<unsigned int>>& received_matrix) {
    int rows = received_matrix.size();
    int cols = received_matrix[0].size();

    // Kiểm tra xem số lượng bit nhận có đủ không
    if (cols < 8) {
        return false; // Không đủ bit
    }

    // Kiểm tra các hàng
    for (int i = 0; i < rows; i++) {
        unsigned int xor_result = 0;
        for (int j = 0; j < cols - 1; j++) { // Không tính cột cuối
            xor_result ^= received_matrix[i][j];
        }
        // So sánh với bit kiểm soát lỗi
        if (xor_result != received_matrix[i][cols - 1]) {
            return false; // Lỗi phát hiện
        }
    }

    // Kiểm tra các cột
    vector<unsigned int> column_xor(cols, 0);
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            column_xor[j] ^= received_matrix[i][j];
        }
    }

    // Kiểm tra so sánh với mã kiểm soát lỗi
    for (int j = 0; j < cols; j++) {
        if (column_xor[j] != (received_matrix[rows - 1][j] ^ 1)) { // Đảo bit
            return false; // Lỗi phát hiện
        }
    }

    return true; // Không có lỗi
}

// Hàm sửa lỗi
void BCC::correct_error(vector<vector<unsigned int>>& received_matrix) {
    int rows = received_matrix.size();
    int cols = received_matrix[0].size();

    for (int i = 0; i < rows; i++) {
        unsigned int xor_result = 0;
        for (int j = 0; j < cols - 1; j++) {
            xor_result ^= received_matrix[i][j];
        }
        if (xor_result != received_matrix[i][cols - 1]) {
            received_matrix[i][0] ^= 1;
        }
    }
}


// Hàm xuất ra màn hình ma trận sau khi đã bỏ đi mã kiểm soát lỗi BCC
void BCC::display_matrix_without_bcc() {
    cout << "Ma trận sau khi đã bỏ đi mã kiểm soát lỗi:" << endl;
    int rows = matrix.size();
    int cols = matrix[0].size() - 1;  // Loại bỏ cột chứa mã kiểm soát lỗi

    for (int i = 0; i < rows - 1; i++) {  // Bỏ qua hàng cuối cùng (chứa mã kiểm soát lỗi)
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


class AMI {
    public:
        vector<float> bits_to_voltage_fixed(const vector<unsigned int>& bits);
        vector<float> bits_to_voltage_custom(const vector<unsigned int>& bits);
        void plot_voltage_wave(const vector<float>& voltages);
};

// Hàm chuyển từ chuỗi bit 0, 1 thành các mức điện áp cố định (bit 0 là 3V, bit 1 là xen kẽ giữa 5V và 1V)
vector<float> AMI::bits_to_voltage_fixed(const vector<unsigned int>& bits) {
    vector<float> voltages;
    bool alternate = true; 

    for (unsigned int bit : bits) {
        if (bit == 0) {
            voltages.push_back(3.0); 
        } else {
            if (alternate) {
                voltages.push_back(5.0);
            } else {
                voltages.push_back(1.0);
            }
            alternate = !alternate;
        }
    }

    return voltages;
}

// Hàm chuyển từ chuỗi bit 0, 1 thành các mức điện áp nhập từ bàn phím (U1 và U3 là mức của bit 1, U2 là mức của bit 0)
vector<float> AMI::bits_to_voltage_custom(const vector<unsigned int>& bits) {
    float U1, U2, U3;

    // Nhập các mức điện áp U1, U2, U3 từ bàn phím với điều kiện |U1 - U2| = |U2 - U3|
    cout << "Nhap U1 (muc dien ap cho bit 1): ";
    cin >> U1;
    cout << "Nhap U2 (muc dien ap cho bit 0): ";
    cin >> U2;

    // Tính U3 dựa trên điều kiện |U1 - U2| = |U2 - U3|
    U3 = 2 * U2 - U1;

    // Kiểm tra điều kiện hợp lệ của U1, U2, U3
    if (fabs(U1 - U2) != fabs(U2 - U3)) {
        cout << "Dien ap U1, U2, U3 khong thoa man dieu kien |U1 - U2| = |U2 - U3|." << endl;
        return {};
    }

    // Chuyển chuỗi bit 0, 1 thành các mức điện áp
    vector<float> voltages;
    bool alternate = true;  // Biến này dùng để xen kẽ giữa U1 và U3 cho bit 1

    for (unsigned int bit : bits) {
        if (bit == 0) {
            voltages.push_back(U2);  // Bit 0 được gán U2
        } else {
            if (alternate) {
                voltages.push_back(U1);  // Bit 1 đầu tiên được gán U1
            } else {
                voltages.push_back(U3);  // Bit 1 thứ hai được gán U3
            }
            alternate = !alternate;  // Đảo xen kẽ giữa U1 và U3
        }
    }

    return voltages;
}

// Hàm vẽ đồ thị sóng điện áp từ các mức điện áp sử dụng matlabcpp

// void AMI::plot_voltage_wave(const vector<float>& voltages) {
//     vector<float> time(voltages.size());
    
//     // Tạo mảng thời gian tương ứng với các bit (giả sử mỗi bit kéo dài 1 đơn vị thời gian)
//     for (int i = 0; i < time.size(); ++i) {
//         time[i] = i;
//     }
    
//     // Sử dụng các hàm từ matlabcpp để vẽ đồ thị
//     matlab::Figure fig;
//     fig.plot(time, voltages);  // Vẽ đồ thị giữa thời gian và điện áp
//     fig.xlabel("Thoi gian");
//     fig.ylabel("Dien ap (V)");
//     fig.title("Do thi song dien ap AMI");
//     fig.grid(true);
    
//     fig.show();  // Hiển thị đồ thị lên màn hình
// }


class Manage {
private:
    UNICODE_UTF8 unicode;     
    BCC *bcc;                  
    AMI *ami;                  
    vector<uint8_t> input_characters; // Chuỗi ký tự được nhập từ bàn phím
    vector<vector<unsigned int>> bit_matrix; // Ma trận các bit sau khi mã hóa
    vector<float> voltage_waveform; // Chuỗi điện áp sau khi chuyển đổi sang mã AMI

public:
    Manage();
    void display_menu();
    void execute_option(int);                       
    void display_unicode_table();
    void get_user_input();     
    void encode_to_bits();     
    void add_bcc_code();       
    void convert_to_ami();     
    void display_signal_wave(); 
    void decode_from_signal();  
    void check_for_errors();   
    void correct_errors();     
    void extract_bits();        
    void display_unicode_characters(); 

    // Hàm phụ trợ chuyển đổi từ sóng tín hiệu về dạng bit
    vector<unsigned int> voltage_to_bits(const vector<float>& voltages) {
        vector<unsigned int> bits;
        for (float voltage : voltages) {
            if (voltage == 5) { // Mức điện áp cao nhất
                bits.push_back(1);
            } else if (voltage == 3) { // Mức điện áp trung bình
                bits.push_back(0);
            } else { // Mức điện áp thấp nhất
                bits.push_back(0);
            }
        }
        return bits;
    }
};

// Hàm hiển thị sóng tín hiệu
void Manage::display_signal_wave() {
    cout << "Sóng tín hiệu (các mức điện áp): " << endl;
    for (float voltage : voltage_waveform) {
        cout << voltage << "V "; // Hiển thị từng mức điện áp
    }
    cout << endl;
}

// Hàm chuyển từ sóng tín hiệu về dạng mã BCC
vector<vector<unsigned int>> UNICODE_UTF8::decimal_to_binary_uint_8(const vector<uint8_t> &decimals) {
    vector<vector<unsigned int>> binary_matrix;
    for (unsigned int dec : decimals) {
        vector<unsigned int> binary_row(8, 0); // Tạo một hàng có 8 bit, khởi tạo tất cả bằng 0
        int index = 7; // Lưu vào vector theo thứ tự ngược
        while (dec > 0 && index >= 0) {
            binary_row[index] = dec % 2;
            dec = dec / 2;
            index--;
        }
        binary_matrix.push_back(binary_row);
    }
    return binary_matrix;
}


// Hàm kiểm tra lỗi
void Manage::check_for_errors() {
    if (bcc->check_error(bit_matrix)) {
        cout << "Không phát hiện lỗi trong dữ liệu." << endl;
    } else {
        cout << "Phát hiện lỗi trong dữ liệu!" << endl;
    }
}

// Hàm sửa lỗi
void Manage::correct_errors() {
    bcc->correct_error(bit_matrix);
    cout << "Đã sửa lỗi, ma trận hiện tại: " << endl;
    for (const auto &row : bit_matrix) {
        for (const auto &bit : row) {
            cout << bit << " "; // Hiển thị từng bit
        }
        cout << endl; // Xuống dòng sau mỗi hàng
    }
}

// Hàm chuyển về dạng chuỗi bit 0 và 1
void Manage::extract_bits() {
    cout << "Chuỗi bit sau khi bỏ đi mã kiểm soát lỗi BCC: " << endl;
    vector<unsigned int> bits;
    
    for (const auto &row : bit_matrix) {
        for (size_t i = 0; i < row.size() - 1; ++i) { // Bỏ qua cột cuối (mã kiểm soát lỗi)
            bits.push_back(row[i]);
        }
    }

    // Hiển thị từng byte (8 bit)
    for (size_t i = 0; i < bits.size(); i += 8) {
        if (i + 7 < bits.size()) {
            uint8_t byte = 0;
            for (size_t j = 0; j < 8; ++j) {
                byte |= (bits[i + j] << (7 - j)); // Ghép từng bit thành byte
            }
            cout << "Byte " << (i / 8) + 1 << ": " << static_cast<int>(byte) << endl; // Hiển thị giá trị byte
        }
    }
}

// Hàm hiển thị các ký tự UNICODE
void Manage::display_unicode_characters() {
    cout << "Các ký tự UNICODE tương ứng: " << endl;
    for (const auto &byte : input_characters) {
        cout << static_cast<char>(byte); // Hiển thị từng ký tự
    }
    cout << endl;
}

// Hàm hiển thị menu
void Manage::display_menu() {
    cout << "====================== MENU ======================" << endl;
    cout << "1. Hiển thị bảng mã UNICODE_UTF8" << endl;
    cout << "2. Nhập vào chuỗi ký tự" << endl;
    cout << "3. Hiển thị chuỗi ký tự đã mã hóa thành bit 0 và 1" << endl;
    cout << "4. Hiển thị ma trận sau khi thêm mã kiểm soát lỗi BCC" << endl;
    cout << "5. Hiển thị chuỗi điện áp sau khi chuyển sang mã AMI" << endl;
    cout << "6. Hiển thị sóng tín hiệu" << endl;
    cout << "7. Chuyển từ sóng tín hiệu về dạng mã BCC" << endl;
    cout << "8. Kiểm tra lỗi" << endl;
    cout << "9. Sửa lỗi" << endl;
    cout << "10. Chuyển về dạng chuỗi bit 0 và 1" << endl;
    cout << "11. Hiển thị các ký tự UNICODE" << endl;
    cout << "0. Thoát" << endl;
    cout << "=============================================" << endl;
}

// Hàm thực hiện tùy chọn
void Manage::execute_option(int option) {
    switch (option) {
        case 1:
            display_unicode_table();
            break;
        case 2:
            get_user_input();
            break;
        case 3:
            encode_to_bits();
            break;
        case 4:
            add_bcc_code();
            break;
        case 5:
            convert_to_ami();
            break;
        case 6:
            display_signal_wave();
            break;
        case 7:
            decode_from_signal();
            break;
        case 8:
            check_for_errors();
            break;
        case 9:
            correct_errors();
            break;
        case 10:
            extract_bits();
            break;
        case 11:
            display_unicode_characters();
            break;
        case 0:
            cout << "Thoát chương trình." << endl;
            break;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;
            break;
    }
}
int main() {
    Manage manager; // Tạo đối tượng quản lý
    int option;

    do {
        manager.display_menu(); // Hiển thị menu
        cout << "Nhập lựa chọn của bạn: ";
        cin >> option; // Nhận lựa chọn từ người dùng
        manager.execute_option(option); // Thực hiện tùy chọn
    } while (option != 0); // Lặp lại cho đến khi người dùng chọn thoát

    return 0; // Kết thúc chương trình
}