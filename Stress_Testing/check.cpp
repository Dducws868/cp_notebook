#include <bits/stdc++.h>
using namespace std;

// Hàm hỗ trợ đọc và in nội dung file ra màn hình
void printFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  [Cannot open " << filename << "]\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
}

// Hàm hỗ trợ biên dịch file và kiểm tra lỗi
bool compile(const string& cpp_file, const string& exe_file) {
    cout << "Compiling " << cpp_file << "...\n";
    // Lệnh gọi g++ (có thể thêm -O2 để tối ưu thời gian chạy)
    string cmd = "g++ " + cpp_file + " -o " + exe_file;

    // Thực thi lệnh và lấy mã trả về (0 là thành công)
    int res = system(cmd.c_str());
    if (res != 0) {
        cout << "[ERROR] Compilation failed for " << cpp_file << "!\n";
        return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- BƯỚC BIÊN DỊCH ---
    cout << "=== START COMPILING ===\n";
    if (!compile("gen.cpp", "gen.exe")) return 1; // Dừng nếu gen lỗi
    if (!compile("my.cpp", "my.exe")) return 1;   // Dừng nếu code của bạn lỗi
    if (!compile("correct.cpp", "correct.exe")) return 1; // Dừng nếu code chuẩn lỗi
    cout << "=== COMPILATION SUCCESSFUL ===\n\n";

    // --- BƯỚC CHẠY TEST ---
    int cnt = 0;

    while (true) {
        cnt++;
        cout << "Running on test " << cnt << "..." << endl;

        // Sinh test, chạy code và chạy code chuẩn
        if (system("gen.exe > input.inp") != 0) break;
        if (system("my.exe < input.inp > my.out") != 0) break;
        if (system("correct.exe < input.inp > correct.out") != 0) break;

        // So sánh 2 file output (Dùng fc trên Windows, dùng diff trên Linux/Mac)
        int res = system("fc my.out correct.out > nul");

        if (res != 0) {
            cout << "WA at test " << cnt << "\n\n";

            cout << "=== INPUT ===\n";
            printFile("input.inp");

            cout << "\n=== MY OUTPUT ===\n";
            printFile("my.out");

            cout << "\n=== CORRECT OUTPUT ===\n";
            printFile("correct.out");

            break;
        }
    }

    cout << "\nFinished!\n";
    system("pause");
    return 0;
}
