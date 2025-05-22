Giới thiệu Dự án

Dự án này là một Hệ thống đăng nhập và đăng ký tài khoản và quản lý ví điểm thưởng. Mục đích chính của hệ thống là quản lý quá trình đăng ký tài khoản người dùng, yêu cầu cung cấp thông tin xác thực như tên người dùng và mật khẩu. Khi người dùng đăng ký thành công, hệ thống sẽ tạo một bản ghi dữ liệu (có thể là tập tin) cho người dùng đó. Ngoài ra, dự án còn tích hợp cơ chế quản lý ví điểm thưởng, nơi người dùng có thể sử dụng điểm để quy đổi ra hàng hóa (hoạt động mua - bán). Hệ thống cũng hỗ trợ giao dịch chuyển điểm giữa các ví. Chương trình được viết bằng C++ và có giao diện văn bản, thao tác kiểu nhập dòng lệnh.
Thành viên Dự án và Công việc được giao

Phân tích thiết kế database : Cả nhóm

Đỗ Thị Hằng: (K24DTCN190) - Dựng code-base, dựng Database, phát triển phần xử lý ví, nâng cấp các chức năng liên quan đến người dùng, sửa lỗi, cập nhật README.md, review code của các thành viên khác ( Leader).
Nguyễn Khắc Đức: (K24DTCN124) - Tạo property, hàm contructor của Transaction, transactionstatus, phần display menu trong main.
Nguyễn Hoàng Khôi: (K24DTCN203) - Phát triển các chức năng: Đổi mật khẩu có otp và nâng cấp Login sử dụng otp
Nguyễn Thị Hương: (K24DTCN132) - Phát triển các chức năng: đăng ký, đăng nhập, list toàn bộ user ( có kết nối cơ sở dữ liệu, chưa có OTP), cập nhật README.md

Đặc Tả Hoạt Động Ứng Dụng Quản Lý Ví Điện Tử (CLI)
1. Giới thiệu
Tài liệu này mô tả chi tiết cách thức hoạt động của ứng dụng Quản lý Ví Điện Tử (Wallet Management CLI) từ góc độ người dùng và hệ thống. Ứng dụng này cung cấp giao diện dòng lệnh cho phép người dùng quản lý tài khoản và thực hiện các giao dịch ví điểm thưởng.
2. Tổng quan hệ thống
Ứng dụng là một chương trình giao diện dòng lệnh (CLI) được phát triển bằng C++. Nó tương tác với một cơ sở dữ liệu SQL Server để lưu trữ và quản lý thông tin người dùng, ví và các giao dịch.
2.1. Các vai trò người dùng
Hệ thống phân biệt hai loại người dùng chính:
Người dùng thông thường (User): Có thể thực hiện các thao tác cá nhân liên quan đến tài khoản và ví của họ.
Quản trị viên (Admin): Có tất cả các quyền của người dùng thông thường, cộng thêm các quyền quản lý hệ thống.
2.2. Luồng hoạt động chính
Người dùng tương tác với ứng dụng thông qua một menu chính. Các chức năng sẽ được thực hiện dựa trên lựa chọn của người dùng và trạng thái đăng nhập của họ.
3. Hoạt động chi tiết của các chức năng
3.1. Menu chính và điều hướng
Khi khởi động, ứng dụng sẽ hiển thị một menu chính với các tùy chọn được đánh số:
==========================
  Quan ly vi dien tu
==========================
1. Dang ky
2. Dang nhap
3. Thay doi mat khau
4. Chuyen diem
5. Kiem tra so du vi
6. Lich su giao dich
7. Nap diem
8. Xem danh sach nguoi dung
9. Thoat
==========================
Chon lenh (1-9):

Người dùng nhập số tương ứng với chức năng muốn thực hiện. Sau mỗi thao tác, màn hình sẽ được xóa (system(CLEAR_SCREEN)) và menu sẽ hiển thị lại, chờ lệnh tiếp theo.
3.2. Quản lý người dùng
3.2.1. Đăng ký (Lựa chọn 1)
Điều kiện: Chỉ quản trị viên mới có thể thực hiện chức năng này. Nếu người dùng hiện tại không phải là admin, hệ thống sẽ hiển thị thông báo "Chi admin moi co quyen thuc hien tac vu nay!" và không cho phép đăng ký.
Luồng hoạt động:
Hệ thống yêu cầu nhập ten nguoi dung moi.
Hệ thống yêu cầu nhập mat khau. ( có thể bỏ trống, nếu mật khẩu trống, hệ thống sẽ tự động tạo mật khẩu)
Hệ thống yêu cầu nhập quyen (User/Admin). ( có thể bỏ trống, nếu bỏ trống, mặc định sẽ là quyền User)
Hệ thống cố gắng thêm người dùng mới vào cơ sở dữ liệu.
Kết quả: Thông báo Dang ky thanh cong! hoặc Dang ky that bai!.
3.2.2. Đăng nhập (Lựa chọn 2)
Điều kiện: Không yêu cầu điều kiện đặc biệt.
Luồng hoạt động:
Hệ thống yêu cầu nhập ten nguoi dung.
Hệ thống yêu cầu nhập mat khau.
Hệ thống xác thực thông tin đăng nhập với cơ sở dữ liệu.
Hệ thống hiển thị mã otp lên màn hình, người dùng cần nhập mã OTP, sau đó hệ thống sẽ so sánh mã OTP người dùng nhập với mã được tạo ra trong CSDL
nếu đúng -> đăng nhập 
nếu sai -> không đăng nhập được
Kết quả: Nếu thành công, loggedInUser được thiết lập và thông báo Dang nhap thanh cong!. Nếu thất bại, thông báo Dang nhap that bai!.
3.2.3. Thay đổi mật khẩu (Lựa chọn 3)
Điều kiện: Người dùng phải đang đăng nhập. Nếu không, hệ thống hiển thị Ban chua dang nhap!.
Luồng hoạt động:
Hệ thống yêu cầu nhập mat khau moi.
Hệ thống cập nhật mật khẩu của loggedInUser trong cơ sở dữ liệu.
Kết quả: Thông báo Mat khau da duoc cap nhat thanh cong! hoặc Thay doi mat khau that bai!.
Nếu người dùng đang đăng nhập có quyền Admin -> hệ thống sẽ yêu cầu người dùng nhập UserID của người sẽ được thay đổi mật khẩu.
Sẽ cần verify OTP trong quá trình thay đổi mật khẩu ( tương tự như khi đăng nhập)
3.2.4. Xem danh sách người dùng (Lựa chọn 8)
Điều kiện: Chỉ quản trị viên mới có thể thực hiện chức năng này. Nếu không, hệ thống hiển thị Chi admin moi co quyen thuc hien tac vu nay!.
Luồng hoạt động:
Hệ thống truy xuất tất cả người dùng từ cơ sở dữ liệu.
Kết quả: Hiển thị Danh sach tat ca nguoi dung: với UserId,  UserName và Role của từng người dùng. Nếu không có người dùng nào, thông báo Khong co nguoi dung nao trong he thong..
3.3. Quản lý ví
3.3.1. Chuyển điểm (Lựa chọn 4)
Điều kiện: Người dùng phải đang đăng nhập. Nếu không, hệ thống hiển thị Ban chua dang nhap!.
Luồng hoạt động:
Hệ thống yêu cầu nhập UserId cua nguoi nhan.
Hệ thống yêu cầu nhập so diem can chuyen.
Kiểm tra đầu vào:
Nếu so diem can chuyen <= 0, thông báo So diem chuyen phai lon hon 0!.
Nếu senderId (người gửi) == receiverId (người nhận), thông báo Loi: Ban khong the chuyen diem cho chinh minh!.
Kiểm tra ví người gửi:
Truy vấn số dư ví của người gửi.
Nếu không tìm thấy ví người gửi, thông báo Loi: Khong tim thay vi cua nguoi gui! và ghi nhận giao dịch với StatusId = 2 (Failed).
Nếu số dư không đủ, thông báo So du khong du de chuyen! và ghi nhận giao dịch với StatusId = 2 (Failed).
Kiểm tra ví người nhận:
Truy vấn ví của người nhận.
Nếu không tìm thấy ví người nhận, thông báo Loi: Khong tim thay vi cua nguoi nhan! và ghi nhận giao dịch với StatusId = 2 (Failed).
Thực hiện giao dịch (Atomic):
Cập nhật (UPDATE) số dư ví người gửi: Balance = Balance - @Amount.
Cập nhật (UPDATE) số dư ví người nhận: Balance = Balance + @Amount.
Chèn (INSERT) một bản ghi giao dịch mới vào bảng Transactions với StatusId = 1 (Success).
Kết quả: Thông báo Chuyen diem thanh cong! hoặc Chuyen diem that bai!.
3.3.2. Kiểm tra số dư ví (Lựa chọn 5)
Điều kiện: Người dùng phải đang đăng nhập. Nếu không, hệ thống hiển thị Ban chua dang nhap!.
Luồng hoạt động:
Hệ thống truy vấn số dư ví của loggedInUser từ cơ sở dữ liệu.
Kết quả: Nếu tìm thấy ví, hiển thị So du vi cua ban: [balance]. Nếu không tìm thấy, thông báo Khong tim thay vi cua ban!.
3.3.3. Nạp điểm (Lựa chọn 7)
Điều kiện: Người dùng phải đang đăng nhập. Nếu không, hệ thống hiển thị Ban chua dang nhap!.
Luồng hoạt động:
Hệ thống yêu cầu nhập so diem can nap.
Kiểm tra đầu vào: Nếu so diem nap <= 0, thông báo So diem nap phai lon hon 0!.
Hệ thống kiểm tra ví của người dùng.
Nếu ví đã tồn tại, cập nhật (UPDATE) số dư: Balance = Balance + @Amount.
Nếu ví chưa tồn tại, chèn (INSERT) một ví mới với số dư là Amount đã nạp.
Kết quả: Thông báo Nap diem thanh cong! hoặc Nap diem that bai!.
3.4. Quản lý giao dịch
3.4.1. Lịch sử giao dịch (Lựa chọn 6)
Điều kiện: Người dùng phải đang đăng nhập. Nếu không, hệ thống hiển thị Ban chua dang nhap!.
Luồng hoạt động:
Hệ thống truy xuất lịch sử các giao dịch mà loggedInUser là người gửi từ cơ sở dữ liệu.
Kết quả:
Nếu không có giao dịch nào, thông báo Khong co giao dich nao!.
Nếu có giao dịch, hiển thị Lich su giao dich cua ban: với các thông tin: ID, Nguoi nhan, So tien, Ngay, Trang thai.
3.5. Thoát (Lựa chọn 9)
Luồng hoạt động: Ứng dụng kết thúc.
4. Xử lý lỗi và thông báo
Hệ thống cung cấp các thông báo lỗi cơ bản cho người dùng thông qua giao diện dòng lệnh:
Ban chua dang nhap!
Chi admin moi co quyen thuc hien tac vu nay!
Dang ky that bai!
Dang nhap that bai!
Thay doi mat khau that bai!
Khong co nguoi dung nao trong he thong.
So diem chuyen phai lon hon 0!
Loi: Ban khong the chuyen diem cho chinh minh!
Loi: Khong tim thay vi cua nguoi gui!
So du khong du de chuyen!
Loi: Khong tim thay vi cua nguoi nhan!
Chuyen diem that bai!
Khong tim thay vi cua ban!
Nap diem that bai!
Khong co giao dich nao!
Loi ket noi: [thong bao loi tu he thong] (Lỗi kết nối cơ sở dữ liệu)
Loi!!!. (Lựa chọn không hợp lệ từ menu)
5. Tương tác cơ sở dữ liệu
Hệ thống sử dụng hệ quản trị cơ sở dữ liệu MS SQL 
6. Tải và chạy chương trình:
- Clone project về từ github
- Chạy SQL Management ở máy local, backup database bằng file backup đi kèm trong folder dự án ( nếu máy chưa có MS SQL cần cài SQL server và SQL management)
- Build project bằng Visual studio ( đã cài bộ mở rộng C++/CLR và .Net framwork 4.8)
- Cập nhật file DatabaseManagement: cập nhật connection string theo thông tin kết nối cơ sở dữ liệu tại máy local
- Run dự án và chạy thử ( tham khảo video demo có trong folder dự án)


