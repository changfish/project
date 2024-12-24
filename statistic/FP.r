########################
###    GROUP 10 FP   ###
########################

# read the data -----------------------------------------------------------
data <- read.csv("fp data.csv")

# P.A-1 -------------------------------------------------------------------
f_NTHU <- data[data$學校=="清華大學",]$每學期回家次數
f_NCTU <- data[data$學校=="交通大學",]$每學期回家次數

school<-list(
  N_NTHU = length(f_NTHU),
  N_NCTU = length(f_NCTU),
  fmean_NTHU = mean(f_NTHU),
  fmean_NCTU = mean(f_NCTU),
  fvar_NTHU = sd(f_NTHU)**2,
  fvar_NCTU = sd(f_NCTU)**2,
  z = (mean(f_NTHU) - mean(f_NCTU))/sqrt(sd(f_NTHU)**2/length(f_NTHU)+sd(f_NCTU)**2/length(f_NCTU))
)
t(school)  #print
2*pnorm(-abs(school$z),mean = 0,sd = 1)

# P.A-2 -------------------------------------------------------------------
f_boy <- data[data$性別=="男",]$每學期回家次數
f_girl <- data[data$性別=="女",]$每學期回家次數

gender<-list(
  N_boy = length(f_boy),
  N_girl = length(f_girl),
  fmean_boy = mean(f_boy),
  fmean_girl = mean(f_girl),
  fvar_boy = sd(f_boy)**2,
  fvar_girl = sd(f_girl)**2,
  z = (mean(f_boy) - mean(f_girl))/sqrt(sd(f_boy)**2/length(f_boy)+sd(f_girl)**2/length(f_girl))
)
t(gender)  #print
pnorm(-abs(gender$z),mean = 0,sd = 1)

# P.A-3 -------------------------------------------------------------------
f_Bachelor <- data[data$目前就讀學位=="學士",]$每學期回家次數
f_master <- data[data$目前就讀學位=="碩士",]$每學期回家次數

degree<-list(
  N_Bachelor = length(f_Bachelor),
  N_master = length(f_master),
  fmean_Bachelor = mean(f_Bachelor),
  fmean_master = mean(f_master),
  fvar_Bachelor = sd(f_Bachelor)**2,
  fvar_master = sd(f_master)**2,
  z = (mean(f_Bachelor) - mean(f_master))/sqrt(sd(f_Bachelor)**2/length(f_Bachelor)+sd(f_master)**2/length(f_master))
)
t(degree)  #print
2*pnorm(-abs(degree$z),mean = 0,sd = 1)
# P.A-4 -------------------------------------------------------------------
f_Pet <- data[data$家中是否有養寵物=="是",]$每學期回家次數
f_noPet <- data[data$家中是否有養寵物=="否",]$每學期回家次數
fsd_Pet <- sd(f_Pet)
fsd_noPet <- sd(f_noPet)
pet<-list(
  N_Pet = length(f_Pet),
  N_noPet = length(f_noPet),
  fmean_Pet = mean(f_Pet),
  fmean_noPet = mean(f_noPet),
  fvar_Pet = fsd_Pet**2,
  fvar_noPet = fsd_noPet**2,
  df = 
    floor((fsd_Pet**2/length(f_Pet)+fsd_noPet**2/length(f_noPet))**2/
    (
      (fsd_Pet**2/length(f_Pet))**2/(length(f_Pet)-1)+
      (fsd_noPet**2/length(f_noPet))**2/(length(f_noPet)-1)
     )),
  T = (mean(f_Pet) - mean(f_noPet))/sqrt(fsd_Pet**2/length(f_Pet)+fsd_noPet**2/length(f_noPet))
)
t(pet)  #print
p_value  <- 2 * (pt(-abs(pet$T), pet$df))
p_value

# P.A-5 -------------------------------------------------------------------
f_Dormitory <- data[data$平常在新竹的住宿地點=="學校宿舍",]$每學期回家次數
f_Renting <- data[data$平常在新竹的住宿地點=="在外租屋",]$每學期回家次數

Housing<-list(
  N_Dormitory = length(f_Dormitory),
  N_Renting = length(f_Renting),
  fmean_Dormitory = mean(f_Dormitory),
  fmean_Renting = mean(f_Renting),
  fvar_Dormitory = sd(f_Dormitory)**2,
  fvar_Renting = sd(f_Renting)**2,
  z = (mean(f_Dormitory) - mean(f_Renting))/sqrt(sd(f_Dormitory)**2/length(f_Dormitory)+sd(f_Renting)**2/length(f_Renting))
)
t(Housing)  #print
2*pnorm(-abs(Housing$z),mean = 0,sd = 1)

# P.A-6 -------------------------------------------------------------------
f_single <- data[substr(data$感情狀態,1,2)=="單身",]$每學期回家次數
f_relation <- data[substr(data$感情狀態,1,2)=="交往",]$每學期回家次數

Relationship<-list(
  N_single = length(f_single),
  N_relation = length(f_relation),
  fmean_single = mean(f_single),
  fmean_relation = mean(f_relation),
  fvar_single = sd(f_single)**2,
  fvar_relation = sd(f_relation)**2,
  z = (mean(f_single) - mean(f_relation))/sqrt(sd(f_single)**2/length(f_single)+sd(f_relation)**2/length(f_relation))
)
t(Relationship)  #print
2*pnorm(-abs(Relationship$z),mean = 0,sd = 1)
