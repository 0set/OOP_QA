bool readbmp(char *bmpName) //����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ��еĺ��� 
{
    FILE *fp=fopen(bmpName,"rb");
	//�����ƶ���ʽ��ָ����ͼ���ļ�
    if(fp==0)
      { 
	     return 0;		 
      }
      
    fseek(fp, sizeof(BITMAPFILEHEADER),0);//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
    
    BITMAPINFOHEADER infoheader;  
	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���infoheader��
    
	fread(&infoheader, sizeof(BITMAPINFOHEADER), 1,fp); 
	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ
    
	bmpWidth = infoheader.biWidth;
    bmpHeight = infoheader.biHeight;    
	biBitCount = infoheader.biBitCount;

	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	    
	if(biBitCount==8)//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
      {
        pColorTable=new RGBQUAD[256];
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
        fread(pColorTable,sizeof(RGBQUAD),256,fp);
      }
    
	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pBmpBuf=new unsigned char[lineByte * bmpHeight];
	pBmpBuf0=new unsigned char[lineByte * bmpHeight];
	pBmpBuf1=new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf,1,lineByte * bmpHeight,fp);
	fread(pBmpBuf0,1,lineByte * bmpHeight,fp);
	fread(pBmpBuf1,1,lineByte * bmpHeight,fp);
    fclose(fp);//�ر��ļ�
    return 1;//��ȡ�ļ��ɹ�
}
