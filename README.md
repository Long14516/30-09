# Bài tập Lập trình đa luồng C++

## Thông tin

-   Ngôn ngữ: **C++**
-   Môi trường: **Visual Studio Code**
-   Trình biên dịch: **G++ / MinGW**
-   Nội dung: Thực hành `thread`, `mutex`, Timer mô phỏng bằng
    `sleep_for`, file và xử lý dữ liệu dùng chung.

------------------------------------------------------------------------

# Bài 01 --- Trao đổi dữ liệu qua file

## Yêu cầu

Bài 01 gồm **2 chương trình độc lập**:

-   `1a.cpp` --- CT1
-   `1b.cpp` --- CT2

Hai chương trình sử dụng chung file:

``` text
dulieu.dat
```

## CT1 --- `1a.cpp`

CT1 thực hiện:

1.  Tạo liên tục một số nguyên không âm 4 byte.
2.  Nếu số tạo ra chia hết cho `2021` thì thoát vòng lặp.
3.  Nếu không chia hết cho `2021`, ghi số vào file `dulieu.dat`.
4.  File được mở ở chế độ ghi đè.
5.  Sau khi ghi thì đóng file.
6.  Hàm được đặt vào một `thread`.
7.  `main()` kích hoạt thread.

## CT2 --- `1b.cpp`

CT2 thực hiện:

1.  Liên tục đọc số nguyên từ file `dulieu.dat`.
2.  Đọc được số thì đóng file.
3.  Hiển thị số đọc được.
4.  Nếu số đọc được chia hết cho `2021` thì thoát vòng lặp.
5.  Hàm được đặt vào một `thread`.

## Chạy chương trình

Biên dịch:

``` bash
g++ 1a.cpp -o 1a.exe
g++ 1b.cpp -o 1b.exe
```

Mở **2 Terminal**.

Terminal 1:

``` bash
.\1a.exe
```

Terminal 2:

``` bash
.\1b.exe
```

Hai chương trình chạy đồng thời và trao đổi dữ liệu thông qua:

``` text
dulieu.dat
```

------------------------------------------------------------------------

# Bài 02 --- Hai Task không đồng bộ

## File

``` text
2.cpp
```

## Task1

Task1:

1.  Nhập một chuỗi ký tự từ bàn phím.
2.  Chuỗi được lưu trong biến tổng thể `st`.
3.  Loại bỏ dấu cách ở đầu và cuối chuỗi.
4.  Nếu chuỗi sau khi xử lý là `bye` thì dừng Task1.
5.  Task1 được thực hiện bằng một `thread`.

Ví dụ:

``` text
Nhap chuoi:     Hello
Task2 hien thi: Hello
```

Chuỗi:

``` text
   Hello
```

sẽ được xử lý thành:

``` text
Hello
```

## Task2

Task2:

1.  Liên tục kiểm tra biến `st`.
2.  Hiển thị giá trị mới của `st`.
3.  Nếu `st == "bye"` thì dừng.
4.  Task2 được thực hiện bằng một `thread`.

## Đồng bộ

Hai thread cùng sử dụng biến `st`, vì vậy chương trình sử dụng:

``` cpp
mutex
lock_guard<mutex>
```

để tránh truy cập dữ liệu dùng chung cùng lúc.

## Chạy

``` bash
g++ 2.cpp -o 2.exe
.\2.exe
```

Nhập:

``` text
Hello
C++
IoT
bye
```

Khi nhập `bye`, chương trình kết thúc.

------------------------------------------------------------------------

# Bài 03 --- Hai Timer

## File

``` text
3.cpp
```

Bài này mô phỏng 2 Timer bằng 2 thread.

## Timer1

Timer1:

1.  Nhập một ký tự từ bàn phím.
2.  Lưu ký tự vào biến tổng thể `c`.
3.  Hiển thị mã HEX của ký tự.
4.  Chu kỳ thực hiện: **15 ms**.
5.  Nếu ký tự là `*` thì dừng.

Ví dụ:

``` text
Nhap ky tu: A
Ky tu: A - HEX: 0x41
```

Một số mã HEX:

  Ký tự   HEX
  ------- --------
  A       `0x41`
  B       `0x42`
  a       `0x61`
  0       `0x30`

## Timer2

Timer2:

1.  Liên tục kiểm tra biến `c`.
2.  Phát tiếng beep.
3.  Chu kỳ: **7 ms**.
4.  Nếu `c == '*'` thì dừng.

Chương trình sử dụng hàm Windows:

``` cpp
Beep()
```

## Chạy

``` bash
g++ 3.cpp -o 3.exe
.\3.exe
```

Nhập ký tự:

``` text
A
B
C
```

Sau đó nhập:

``` text
*
```

để kết thúc.

> Bài 03 sử dụng `windows.h` nên chương trình được thiết kế để chạy trên
> Windows.

------------------------------------------------------------------------

# Bài 04 --- Hai Task xử lý số ngẫu nhiên

## File

``` text
4.cpp
```

## Task1

Task1:

1.  Sinh liên tục số nguyên ngẫu nhiên.
2.  Số được sinh trong khoảng:

``` text
1 → 50000
```

3.  Lưu các số đã sinh vào một `vector`.
4.  Dừng khi gặp số:
    -   lớn hơn `10000`
    -   và chia hết cho `2021`.
5.  Task1 được đặt trong một thread.
6.  Chu kỳ mô phỏng khoảng `1 ms`.

Điều kiện dừng:

``` cpp
x > 10000 && x % 2021 == 0
```

Ví dụ một số thỏa mãn:

``` text
14147
```

vì:

``` text
14147 = 2021 × 7
```

## Task2

Task2 chạy đồng thời với Task1.

Task2:

1.  Đọc danh sách số do Task1 tạo.
2.  Tìm số lớn nhất.
3.  Tìm số lớn nhì.
4.  Hiển thị kết quả khi giá trị thay đổi.
5.  Phát tiếng beep khi hiển thị.
6.  Dừng khi Task1 dừng.

Ví dụ:

``` text
Task1 sinh: 1523
Task1 sinh: 8765
Task1 sinh: 2341

----------------------------
Task2
So lon nhat: 8765
So lon nhi: 2341
----------------------------
```

## Đồng bộ dữ liệu

Task1 và Task2 cùng truy cập vector:

``` cpp
vector<int> arr;
```

Do đó chương trình sử dụng:

``` cpp
mutex mtx;
```

và:

``` cpp
lock_guard<mutex>
```

để bảo vệ dữ liệu dùng chung.

## Chạy

``` bash
g++ -std=c++17 4.cpp -o 4.exe
.\4.exe
```

> Bài 04 sử dụng `windows.h` cho chức năng `Beep()` nên chạy trên
> Windows.

------------------------------------------------------------------------

# Kiến thức sử dụng

## 1. Thread

Tạo luồng:

``` cpp
thread t1(task1);
thread t2(task2);
```

Chờ luồng kết thúc:

``` cpp
t1.join();
t2.join();
```

## 2. Mutex

Dùng để bảo vệ dữ liệu dùng chung giữa các thread:

``` cpp
mutex mtx;
```

Khóa mutex:

``` cpp
lock_guard<mutex> lock(mtx);
```

## 3. Sleep

Mô phỏng chu kỳ Timer:

``` cpp
this_thread::sleep_for(
    chrono::milliseconds(10)
);
```

## 4. Random

Sinh số ngẫu nhiên:

``` cpp
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(1, 50000);
```

## 5. File

Ghi file:

``` cpp
ofstream file("dulieu.dat", ios::out);
```

Đọc file:

``` cpp
ifstream file("dulieu.dat");
```

## 6. Beep

Phát âm thanh trên Windows:

``` cpp
Beep(800, 50);
```

------------------------------------------------------------------------

# Cấu trúc thư mục đề nghị

``` text
ltht/
│
├── .vscode/
│
├── 1a.cpp
├── 1a.exe
│
├── 1b.cpp
├── 1b.exe
│
├── 2.cpp
├── 2.exe
│
├── 3.cpp
├── 3.exe
│
├── 4.cpp
├── 4.exe
│
├── dulieu.dat
│
└── README.md
```

## Lệnh biên dịch toàn bộ

``` bash
g++ 1a.cpp -o 1a.exe
g++ 1b.cpp -o 1b.exe
g++ 2.cpp -o 2.exe
g++ 3.cpp -o 3.exe
g++ -std=c++17 4.cpp -o 4.exe
```

## Lưu ý

-   Các file `.exe` có thể được tạo tự động sau khi biên dịch.
-   `dulieu.dat` được sử dụng bởi Bài 01.
-   Bài 01 cần chạy CT1 và CT2 đồng thời để quan sát trao đổi dữ liệu.
-   Bài 03 và Bài 04 sử dụng `windows.h`.
-   Khi có lỗi build, nên kiểm tra lại tên file `.cpp`, compiler G++ và
    phiên bản C++ đang sử dụng.
# 30-09
