import pandas as pd
import tkinter as tk
import threading
import time
import re
import os
from selenium import webdriver
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from PyPDF2 import PdfMerger

# from PIL import Image
# from io import BytesIO
# from fpdf import FPDF

Account = "123"
Password = "456"
with open("acc.txt", "r") as f:
    for line in f:
        if "Account" in line:
            Account = line.split("=")[1].strip().strip('"')
        elif "Password" in line:
            Password = line.split("=")[1].strip().strip('"')

pdf_path = os.getcwd()+"\post_pdf"

prefs={'profile.default_content_settings.popups':0,'download.default_directory':pdf_path,
       "profile.default_content_setting_values.automatic_downloads":1}

# 設定 Chrome 啟動選項
chrome_options = Options()
chrome_options.add_argument("--start-maximized")  # 最大化視窗
chrome_options.add_argument("--disable-notifications")  # 關閉通知
chrome_options.add_argument("--disable-gpu")  # 禁用 GPU 渲染
chrome_options.add_experimental_option("prefs", prefs)

# 启动 DevTools 协议

##### 寄件者資料 需設定
S_data = [
    "咖啡薄霧館-馬銘添", "0912617832", "苗栗縣三義鄉廣盛村八股路館前五巷1-18號",
]



def split_address(address):
    pattern = re.compile(
        r'(.+?[里路街段])'           # 路、街
        r'(.*)$'                # 後續所有部分作為最後一組
    )
    if(address[0]=="台"):
        address = "臺" + address[1:]
    if(address[4]=="區"):
        match = pattern.match(address[5:])
        ans = [address[0:3],address[3:5]]
    else:
        match = pattern.match(address[6:])
        ans = [address[0:3],address[3:6]]
    if match:
        t = [group if group else '' for group in match.groups()]
        ans.append(t[0])
        ans.append(t[1])
        return ans
    return None




input_file = "./test.xlsx"
output_file = "./complete.xlsx"
df = pd.read_excel(input_file,dtype=str)
tem_arr = df.to_numpy()
col_name = df.columns[3:]
R_datas = []
for i in range(0,len(tem_arr)):
    tem = []
    for j in range(0,3):
        tem.append(tem_arr[i][j])
    tem_str = ""
    for j in range(0,len(col_name)):
        if(str(tem_arr[i][j+3])!="nan"):
            tem_str+=col_name[j]+"x"+str(tem_arr[i][j+3])+","
    tem.append(tem_str[:-1])
    R_datas.append(tem)



url = "https://ezpost.post.gov.tw/SingleShip"
index = 0
flag = 1
post_info = []


def post_data(S_data,R_data):
    S_address = split_address(S_data[2])
    if(S_address == None):
        print("寄件人地址格式錯誤")
    #重新整理 回到首頁填寫新資料
    R_address = split_address(R_data[2])
    if(R_address == None):
        print("收件人地址格式錯誤,"+", ".join(R_data))
    radio_button = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.ID, "mailTypeIBox"))
    )
    radio_button.click()
    # 強制點下一步, 進入說明page
    next_button = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.ID, "btn-green"))
    )
    driver.execute_script("arguments[0].click();", next_button)


    # 定位按鈕, 同意說明, 進入填寫寄件人資料
    submit_button = driver.find_element(By.ID, "submitButton")
    # 使用 JavaScript 移除 disabled 屬性
    driver.execute_script("arguments[0].removeAttribute('disabled');", submit_button)
    # 強制點擊按鈕
    driver.execute_script("arguments[0].click();", submit_button)
    time.sleep(1.5)
    

    ##### 寄件人資料
    # S_姓名
    name_input = driver.find_element(By.ID, "MAIL_SNAME")
    name_input.send_keys(S_data[0])
    # S_電話 or mail
    phone_input = driver.find_element(By.ID, "MAIL_SPHONE")
    phone_input.send_keys(S_data[1])
    # S_縣市
    address_selector = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "MAIL_SADD_CITY"))
    )
    select = Select(address_selector)
    select.select_by_visible_text(S_address[0])
    time.sleep(0.5)
    # S_鄉鎮市區
    address_selector = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "MAIL_SADD_AREA"))
    )
    select = Select(address_selector)
    select.select_by_visible_text(S_address[1])
    # S_路街村里
    address_input = driver.find_element(By.ID, "MAIL_SADD_ROAD")
    address_input.send_keys(S_address[2])
    # S_巷弄號
    address_input = driver.find_element(By.ID, "MAIL_SADD_OTHER")
    address_input.send_keys(S_address[3])
    time.sleep(1)
    # 強制點擊按鈕, 進入填寫收件人資料
    submit_button = driver.find_element(By.ID, "next-button-step")
    driver.execute_script("arguments[0].click();", submit_button)
    time.sleep(1.5)

    ##### 收件人資料
    # R_姓名
    name_input =WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "MAIL_RNAME"))
    )
    name_input.send_keys(R_data[0])
    # R_電話 or mail
    phone_input = driver.find_element(By.ID, "MAIL_RPHONE")
    phone_input.send_keys(R_data[1])
    # R_縣市
    address_selector = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "MAIL_RADD_CITY"))
    )
    select = Select(address_selector)
    select.select_by_visible_text(R_address[0])
    time.sleep(1)
    # R_鄉鎮市區
    address_selector = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "MAIL_RADD_AREA"))
    )
    select = Select(address_selector)
    select.select_by_visible_text(R_address[1])
    # R_路街村里
    address_input = driver.find_element(By.ID, "MAIL_RADD_ROAD")
    address_input.send_keys(R_address[2])
    # R_巷弄號
    address_input = driver.find_element(By.ID, "MAIL_RADD_OTHER")
    address_input.send_keys(R_address[3])
    time.sleep(0.5)
    # 強制點擊按鈕, 進入填寫物品資料
    submit_button = driver.find_element(By.ID, "next-button-step")
    driver.execute_script("arguments[0].click();", submit_button)
    time.sleep(2.5)
    ##### 物品資料
    # I_物品種類
    item_selector = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "categoryDropdown"))
    )
    # time.sleep(0.5)
    select = Select(item_selector)
    select.select_by_value("2") #食品
    # size_長寬高
    item_selector = WebDriverWait(driver, 10).until(
        EC.presence_of_element_located((By.ID, "sizeDropdown"))
    )
    select = Select(item_selector)
    select.select_by_value("00H")   #小包裹
    
    submit_button = WebDriverWait(driver, 10).until(
        EC.element_to_be_clickable((By.CSS_SELECTOR, ".button_border.confirm-btn-alert"))
    )
    submit_button.click()


    # I_contents
    text_input = driver.find_element(By.ID, "mailCommentTextarea")
    if(R_data[3]):
        text_input.send_keys(R_data[3])
    # 強制點擊按鈕, 送出資料，並準備爬取qrcode
    submit_button = driver.find_element(By.ID, "next-button-step")
    driver.execute_script("arguments[0].click();", submit_button)
    time.sleep(1)
    # 避免被按
    submit_button = driver.find_element(By.ID, "ConfirmSendMailInfo")
    # driver.execute_script("arguments[0].setAttribute('disabled', 'true')", submit_button)
    label.config(text="資料緩處裡，請不要操作任何網頁上的按鈕")  # 清空文字
    label.pack(pady=20)
    time.sleep(1)
    send_post()
    # send_button.pack(pady=10)

def send_post():
    submit_button = driver.find_element(By.ID, "ConfirmSendMailInfo")
    # 強制點擊按鈕, 送出資料，並準備爬取qrcode
    driver.execute_script("arguments[0].click();", submit_button)
    time.sleep(0.5)
    submit_button = driver.find_element("xpath", "//button[text()='確認寄件']")
    driver.execute_script("arguments[0].click();", submit_button)
    time.sleep(0.5)
    submit_button = driver.find_element(By.XPATH, "//button[@data-bs-dismiss='modal' and text()='確認寄件']")
    driver.execute_script("arguments[0].click();", submit_button)
    time.sleep(0.5)
    global index    # to find global var
    index+=1
    # send_button.pack_forget()
    # start_button.pack(pady=10)
    label.config(text="資料輸入中")
    label.pack(pady=20)
    time.sleep(2)
    driver.implicitly_wait(5)
    custom_table = driver.find_element(By.CLASS_NAME, "custom-table")
    table_data_elements = custom_table.find_elements(By.CLASS_NAME, "table-data")
    table_data = [element.text.strip() for element in table_data_elements]
    post_info.append(table_data)
    print(post_info)
    re_run_post_web()




def main_sys():
    start_button.pack_forget()
    driver.get(url)
    global index    # to find global var
    if(index==len(R_datas)):
        # 爬取寄件資料
        driver.get("https://ezpost.post.gov.tw/IBoxStatus")
        time.sleep(5)  # 等待请求完成
        label.config(text="準備下載確認單\n請不要做任何操作")
        label.pack(pady=50)
        download_post_pdf()
        return
    post_data(S_data,R_datas[index])
    


def download_post_pdf():
    ## 確保路徑存在
    if not os.path.exists(pdf_path):
        os.makedirs(pdf_path)
    tem_file_path = os.path.join(pdf_path, "tem.txt")
    with open(tem_file_path,'w') as f:
        f.write("tem write")
    for tem_file_name in os.listdir(pdf_path):
        tem_file_path = os.path.join(pdf_path, tem_file_name)
        if os.path.isfile(tem_file_path):
            os.remove(tem_file_path)
    ##下載pdf到路徑
    ibox_url = "https://ezpost.post.gov.tw/IBoxStatus?page="
    driver.get(ibox_url+str(1))
    time.sleep(1)
    ibox_info = driver.find_element(By.XPATH, "//div[@id='iboxStatusDiv']")
    child_elements = ibox_info.find_elements(By.XPATH,"//div[@class='d-flex flex-wrap justify-content-center whie_block_border_100 ']")
    #總共有多少頁的info
    max_page = driver.find_element(By.XPATH, "//nav[@aria-label='Page navigation ']").find_elements(By.TAG_NAME,"li")[4].text
    max_page = int(max_page)
    info_index = len(post_info)-1
    for page in range(1,max_page+1):
        driver.get(ibox_url+str(page))
        time.sleep(1)
        ibox_info = driver.find_element(By.XPATH, "//div[@id='iboxStatusDiv']")
            
        child_elements = ibox_info.find_elements(By.XPATH,"//div[@class='d-flex flex-wrap justify-content-center whie_block_border_100 ']")
        for c in child_elements:
            if(c.text.split('\n')[3]==post_info[info_index][0]):
                print(c.find_elements(By.TAG_NAME, "span")[0].text)
                print(c.text.split('\n'))
                button = c.find_element(By.CLASS_NAME, "Js-Index-Print")
                driver.execute_script("arguments[0].click();", button)
                time.sleep(2)
                info_index-=1
            else:
                break
            if(info_index<0):
                break
        if(info_index<0):
            break
    pdf_merger = PdfMerger()
    pdf_files = [f for f in os.listdir(pdf_path) if f.endswith('.pdf')]
    for pdf in pdf_files:
        tem_pdf_path = os.path.join(pdf_path, pdf)
        pdf_merger.append(tem_pdf_path)
    output_path = os.path.join(pdf_path, "post_info.pdf")
    pdf_merger.write(output_path)
    pdf_merger.close()
    for tem_file_name in os.listdir(pdf_path):
        if(tem_file_name=="post_info.pdf"):
            continue
        tem_file_path = os.path.join(pdf_path, tem_file_name)
        if os.path.isfile(tem_file_path):
            os.remove(tem_file_path)
    label.config(text="輸入完成,\n請檢查寄件資料(存放至post_crawler資料夾)\n檔名為post_info")
    label.pack(pady=50)
    driver.quit()



def re_run_post_web():
    threading.Thread(target=main_sys).start()





# 建立主視窗
root = tk.Tk()
root.title("Selenium with UI")
root.geometry("1000x500")
# 啟動主視窗迴圈
for t_r in R_datas:
    print(t_r)
    if split_address(t_r[2])== None:
        flag = 0

if flag==1:
    # 登入
    driver = webdriver.Chrome(options=chrome_options)
    driver.get("https://ezpost.post.gov.tw/Account/Login")

    Login_input = driver.find_element(By.ID, "inputEmail")
    Login_input.send_keys(Account)
    Login_input = driver.find_element(By.ID, "inputPd")
    Login_input.send_keys(Password)
    # 建立標籤
    label = tk.Label(root, text="請先登入，登入完成後再開始填入資料", font=("Arial", 12))
    label.pack(pady=20)

    # 建立 "填入資料" 按鈕
    start_button= tk.Button(root,text="填入資料",font=("Arial", 12), command=re_run_post_web)
    send_button = tk.Button(root, text="確認", font=("Arial", 12), command=send_post)
    start_button.pack(pady=10)
    root.mainloop()
else:
    t=""
    for t_r in R_datas:
       if split_address(t_r[2])== None:
            for r in t_r:
                t+=r+" "
            t+="\n"
    print("good")
    t+="\n\n以上資料有誤，導致程式預處理失敗\n請確認地址無誤修正後再重啟程式"+"\n"
    label = tk.Label(root, text=t, font=("Arial", 12))
    label.pack(pady=20)
    root.mainloop()
