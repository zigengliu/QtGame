//        for(size_t i=0;i<boardSize;i++){
//            for(size_t j=0;j<boardSize;j++){
//                if(i==0){
//                    int wallX0[14] = {3,4,5,6,7,8,9,10,11,12,13,14,15,19};
//                    for(size_t h=0;h<14;h++){
//                        if(j==wallX0[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==1){
//                    int wallX1[7]={0,1,3,10,11,17,19};
//                    for(size_t h=0;h<7;h++){
//                        if(j==wallX1[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==2){
//                    int wallX2[15]={0,1,3,5,6,7,8,10,11,13,14,15,17,18,19};
//                    for(size_t h=0;h<15;h++){
//                        if(j==wallX2[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==3){
//                    int wallX3[12]={3,5,6,7,8,10,11,13,14,17,18,19};
//                    for(size_t h=0;h<12;h++){
//                        if(j==wallX3[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==4){
//                    int wallX4[13]={1,2,3,7,8,10,11,13,14,16,17,18,19};
//                    for(size_t h=0;h<13;h++){
//                        if(j==wallX4[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==5){
//                    int wallX5[6]={5,7,8,10,11,19};
//                    for(size_t h=0;h<6;h++){
//                        if(j==wallX5[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==6){
//                    int wallX6[15]={1,2,3,4,5,7,8,10,11,13,14,15,16,17,19};
//                    for(size_t h=0;h<15;h++){
//                        if(j==wallX6[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==7){
//                    int wallX7[9]={0,1,2,7,8,10,11,17,19};
//                    for(size_t h=0;h<9;h++){
//                        if(j==wallX7[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==8){
//                    int wallX8[14]={0,1,2,4,5,6,7,8,10,11,13,14,17,19};
//                    for(size_t h=0;h<14;h++){
//                        if(j==wallX8[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==9){
//                    int wallX9[14]={0,1,2,4,5,6,7,8,10,11,13,14,17,19};
//                    for(size_t h=0;h<14;h++){
//                        if(j==wallX9[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==10){
//                    int wallX10[14]={0,1,2,4,5,6,7,8,10,11,13,14,17,19};
//                    for(size_t h=0;h<14;h++){
//                        if(j==wallX10[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==11){
//                    int wallX11[14]={0,1,2,4,5,6,7,8,10,11,13,14,17,19};
//                    for(size_t h=0;h<14;h++){
//                        if(j==wallX11[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==12){
//                    int wallX12[14]={0,1,2,4,5,6,7,8,10,11,13,16,17,19};
//                    for(size_t h=0;h<14;h++){
//                        if(j==wallX12[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==13){
//                    int wallX13[13]={0,4,5,6,7,8,10,11,13,15,16,19};
//                    for(size_t h=0;h<13;h++){
//                        if(j==wallX13[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==14){
//                    int wallX14[14]={0,2,3,4,5,6,7,8,9,10,11,13,15,19};
//                    for(size_t h=0;h<14;h++){
//                        if(j==wallX14[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==15){
//                    int wallX15[7]={0,4,10,11,13,17,19};
//                    for(size_t h=0;h<7;h++){
//                        if(j==wallX15[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==16){
//                    int wallX16[12]={0,2,4,6,8,10,11,13,14,15,17};
//                    for(size_t h=0;h<12;h++){
//                        if(j==wallX16[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==17){
//                    int wallX17[11]={0,1,2,4,6,8,10,11,15,17,18};
//                    for(size_t h=0;h<11;h++){
//                        if(j==wallX17[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else if(i==18){
//                    int wallX18[10]={0,1,2,6,8,10,11,12,13,15};
//                    for(size_t h=0;h<10;h++){
//                        if(j==wallX18[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }
//                else{
//                    int wallX19[10]={0,1,2,4,5,6,15,16,17,18};
//                    for(size_t h=0;h<10;h++){
//                        if(j==wallX19[h]){
//                            wallPositions[k] = new QPoint(i,j);
//                            k++;
//                        }
//                    }
//                }

//            }
//         }

//        for(size_t i=0;i<boardSize;i++){
//            for(size_t j=0;j<boardSize;j++){
//                if(i==3||j==4){
//                    wallPositions[k] = new QPoint(i,j);
//                    k++;
//                }
//            }
//        }

//        for(size_t i=0;i<boardSize;i++){
//            for(size_t j=0;j<boardSize;j++){
//                if((i==3||j==4)&&!(i==3&&j==3)&&!(i==4&&j==4)){
//                    wallPositions[k] = new QPoint(i,j);
//                    k++;
//                }
//            }
//        }
