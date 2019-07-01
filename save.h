//����ͼƬ���� 
bool savebmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable)
{
    if(!imgBuf)
      {
	     return 0;
	  }//���λͼ����ָ��Ϊ0����û�����ݴ��룬�������� 

    int colorTablesize=0;
    if(biBitCount==8)
      {
          colorTablesize=1024;
      }//��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0 

	int lineByte=(width * biBitCount/8+3)/4*4;
    //���洢ͼ������ÿ���ֽ���Ϊ4�ı���

    FILE *fp=fopen(bmpName,"wb");
    //�Զ�����д�ķ�ʽ���ļ�
    if(fp==0)
      {
          return 0;
      }

    BITMAPFILEHEADER fileHead;
    //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ

    fileHead.bfType = 0x4D42;
	//bmp����

    fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ colorTablesize + lineByte*height;
    //bfSize��ͼ���ļ�4����ɲ���֮��

    fileHead.bfReserved1 = 0;
    fileHead.bfReserved2 = 0;

    fileHead.bfOffBits=54+colorTablesize;
    //bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��

    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
      //д�ļ�ͷ���ļ�

    BITMAPINFOHEADER head;  //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
    head.biBitCount=biBitCount;
    head.biClrImportant=0;
    head.biClrUsed=0;
    head.biCompression=0;
    head.biHeight=height;
    head.biPlanes=1;
    head.biSize=40;
    head.biSizeImage=lineByte*height;
    head.biWidth=width;
    head.biXPelsPerMeter=0;
    head.biYPelsPerMeter=0;

    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
    //дλͼ��Ϣͷ���ڴ�

    if(biBitCount==8)
       {
	       fwrite(pColorTable, sizeof(RGBQUAD),256, fp); //����Ҷ�ͼ������ɫ��д���ļ� 
       }

    fwrite(imgBuf, height*lineByte, 1, fp);
     //дλͼ���ݽ��ļ�

    fclose(fp);
    //�ر��ļ�
    
    return 1;
}
