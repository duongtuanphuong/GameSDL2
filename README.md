# GameSDL2
## Giới thiệu game
  ![Screenshot_1](https://user-images.githubusercontent.com/43140650/169944230-360a7523-89b3-4ed1-b8b9-4bb0a78cce51.png)
  
  Dự án game Soldier là một trò chơi đi cảnh bắn súng.Các ý tưởng chính của dự án:
  - Người chơi sẽ điều khiển một nhân vật đi qua các màn chơi tiêu diệt các mục tiêu đối địch
  - Mỗi màn chơi sẽ có nhiều loại mục tiêu đối địch với cách thức di chuyển và tấn công khác nhau
  - Mỗi màn chơi sẽ có các vật phẩm hỗ trợ như tiền vàng, thêm mạng người chơi, các loại đạn,....
  - Mỗi màn chơi có thể có thêm các BOSS.
  
 ## Cài đặt chương trình
  - Khi code mình đã sử dụng Visual studio 2012 nên đã tránh lỗi thì mọi người hãy dùng nó để chạy thử demo.
  ![Screenshot_2](https://user-images.githubusercontent.com/43140650/169954547-4ff41ec5-aacf-4c28-8717-4d8993c2a3c5.png)
  - Sau khi vào được code thì F7 để build và F5 để chạy game.
 ## Các chức năng đã cài đặt
  - Dựng hình ảnh backgroud trò chơi
  - Xây dựng bản đồ map cho trò chơi
  - Load hình ảnh nhân vật, và cơ chế di chuyển cho nhân vật
  - Load hình ảnh mục tiêu, cơ chế di chuyển của mục tiêu
  - Xây dựng đạn bán cho nhân vật và mục tiêu
  - Xử lý va chạm của nhân vật, mục tiêu với map
  - Xử lý va chạm của đạn bắn nhân vật và mục tiêu
  - Xử lý va chạm giữa nhân vật và mục tiêu
  
  Video demo code : https://www.youtube.com/watch?v=t_Qi0WU3uHY
## Các kỹ thuật lập trình 
  - Chương trình được chia ra làm nhiều class để xử lý cho từng đối tượng. Vd : Nhân vật <-> MainObject, Mục tiêu <-> ThreatObject,.....
  - Các Struct được khai báo chung trong CommonFunc.h để các Class kế thừa có thể tái sử dụng
  - Mảng và con trỏ dùng nhiều trong các hàm
  - ......

## Kết luận
  - Code chương trình chưa hoàn thiện, còn xuất hiện nhiều lỗi cần tiếp tục hoàn thiện
  - Thuật toán di chuyển cho các mục tiêu còn đơn giản
  - Code chưa clean
  - Tốc độ game chậm, thỉnh thoảng vẫn bị treo hình ảnh
  
  Hướng phát triển cho dự án :
    - Thêm các cơ chế cho game : thêm mạng, tiền thêm điểm, boss,....
    - Xây dựng thuật toán cho các mục tiêu thông minh hơn
    - Cập nhật, chỉnh sửa các lỗi còn tồn đọng trong game
    - Tối ưu lại code, tìm giải pháp mới hay hơn
