ngaunhien.c : linux kernel module để tạo ra số ngẫu nhiên
Khởi tạo số ngẫu nhiên sử dụng hàm get_random_bytes từ thư viện linux/random.h
Cách chạy:	
Gõ make-> sudo insmod ngaunhien.ko ->dmesg để theo dõi quá trình hoạt động của module -> sudo rmmod ngaunhien.ko
randomdevice.c: character device để tạo ra số ngẫu nhiên và cho phép các tiến trình ở userspace có thể open và read các số ngẫu nhiên.
+static int __init chardevran_init(void):Khởi tạo khi xây dựng một driver.Hàm sẽ được gọi khi module được load lên
	.Đầu tiên hàm đăng ký với hệ thống để cấp cho một major number(majornum).Nếu majornum<0 -> đăng ký thất bại
	.Tiếp theo đăng ký một device class :ranclass=class_create(THIS_MODULE,class_name); . Hàm này sẽ trả về một con trỏ hàm đến class device được khởi tạo nếu thành công, Nếu thất bại thì hủy bỏ đi số majornum đã đăng ký. Sau đó hiển thị màn hình việc đăng ký thất bại.
	.Cuối cùng đăng ký một driver:randevice=device_create(ranclass,NULL,MKDEV(majornum,0),NULL,device_name);. Nếu thất bại hủy bỏ class và major number vừa mới đăng ký.
+static void __exit chardevran_exit(void):Lần lượt hủy bỏ những con trỏ đã được cấp phát và hủy đăng ký major number.
+static ssize_t dev_read(struct file *filep,char *buffer, size_t len,loff_t *offset):
	.Hàm được gọi khi userspace muốn truy cập dữ liệu từ device
	.Dùng hàm get_random_bytes để tạo một số ngẫu nhiên có kích thước sizeof(char) và được lưu vào biến rannum
	.Sau đó tách từng chữ số đưa vào chuỗi buffer. Đầu ra sẽ là chuỗi chứa các chữ số
Cách chạy:
Gõ make -> sudo insmod randomdevice.ko -> sudo ./test ->dmesg->sudo rmmod randomdevice.ko


