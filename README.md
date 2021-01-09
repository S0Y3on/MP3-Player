# MP3-Player
자료구조 과제
======================

## 프로그램 실행 예시
* 사용할 데이터 파일 로드 
    ```
    Data file name ? my_collection.txt  
    ```
* 가수 이름 (알파벳 정렬), 노래 제목 (알파벳 정렬), 파일 경로  
    ```
    $ status
      2: AOA, 심쿵해, C:\\Music\AOA\심쿵해.mp3
      1: BIGBANG, BAE BAE, C:\\Music\BIGBANG\BAE BAE.mp3
      5: BIGBANG, LOSER, C:\\Music\BIGBANG\LOSER.mp3
      6: BIGBANG, 맨정신, C:\\Music\BIGBANG\맨정신.mp3
      4: 아이유, 무릎, C:\\Music\아이유\무릎.mp3
      3: 아이유, 새 신발, C:\\Music\아이유\새 신발.mp3    
    ```
* 노래파일 추가
    ```
   $ add
     Artist: 아이유
     Title: Twenty three
     File: C:\\Music\아이유\twenty-three.mp3
    ```
* 노래파일 검색
    ```
   $ search
     Artist: AOA
     Title: 심쿵해
   $ Found:
       2: AOA, 심쿵해, C:\\Music\AOA\심쿵해.mp3 
    ```
* 노래파일 재생, 목록에서 삭제 (노래 번호사용) , 목록 파일에 저장, 종료
    ```
   $ play 4 
   $ remove 6
   $ save as my_collection.txt
   $ exit
   ```
