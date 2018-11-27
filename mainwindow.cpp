#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFlagProcessed(false);
    this->setValidExtensions();
    this->setPropertiesOnQTableWidget();
//    this->mPlayer = new QMediaPlayer(this);
    //connect(this->mPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
//    this->mPlayer->setMedia(QUrl::fromLocalFile("/home/pepe/DATOS/PRUEBAS/TijuanaSantos/folder_of_chunks/chunk_000000.avi"));
//    QStringList metadatalist = this->mPlayer->availableMetaData();
    //int list_size = metadatalist.size();
    //std::cout << "Size: " << list_size << std::endl;
    //this->GetMetaData(this->mPlayer);
    av_register_all();

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getNumberOfVideosIncorrect() const
{
    return numberOfVideosIncorrect;
}

void MainWindow::setNumberOfVideosIncorrect(int value)
{
    numberOfVideosIncorrect = value;
}

int MainWindow::getNumberOfVideos() const
{
    return numberOfVideos;
}

void MainWindow::setNumberOfVideos(int value)
{
    numberOfVideos = value;
}

bool MainWindow::getFlagProcessed() const
{
    return flagProcessed;
}

void MainWindow::setFlagProcessed(bool value)
{
    flagProcessed = value;
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia)
        GetMetaData(this->mPlayer);
}

void MainWindow::GetMetaData(QMediaPlayer *player)
{
   // Get the list of keys there is metadata available for
   QStringList metadatalist = player->availableMetaData();

   // Get the size of the list
   int list_size = metadatalist.size();

   //qDebug() << player->isMetaDataAvailable() << list_size;

   // Define variables to store metadata key and value
   QString metadata_key;
   QVariant var_data;

   std::cout << "Size: " << list_size << std::endl;
   for (int indx = 0; indx < list_size; indx++)
   {
     // Get the key from the list
     metadata_key = metadatalist.at(indx);

     // Get the value for the key
     var_data = player->metaData(metadata_key);

    qDebug() << metadata_key << var_data.toString();
   }
 }

/**
 * @brief      Sets the valid extensions.
 */
void MainWindow::setValidExtensions(){
    this->qslValidExtensions.push_back("*.avi");
    this->qslValidExtensions.push_back("*.AVI");
    this->qslValidExtensions.push_back("*.mp4");
    this->qslValidExtensions.push_back("*.MP4");
}

/**
 * @brief      Gets the directory in.
 *
 * @return     The directory in.
 */
QDir MainWindow::getDirectoryIn() const
{
    return directoryIn;
}

/**
 * @brief      Sets the directory in.
 *
 * @param[in]  value  The value
 */
void MainWindow::setDirectoryIn(const QDir &value)
{
    directoryIn = value;
}

/**
 * @brief      Gets the current output path.
 *
 * @return     The current output path.
 */
std::string MainWindow::getCurrentOutputPath() const
{
    return currentOutputPath;
}

/**
 * @brief      Sets the current output path.
 *
 * @param[in]  value  The value
 */
void MainWindow::setCurrentOutputPath(const std::string &value)
{
    currentOutputPath = value;
}

/**
 * @brief      Gets the current input path.
 *
 * @return     The current input path.
 */
std::string MainWindow::getCurrentInputPath() const
{
    return currentInputPath;
}

/**
 * @brief      Sets the current input path.
 *
 * @param[in]  value  The value
 */
void MainWindow::setCurrentInputPath(const std::string &value)
{
    currentInputPath = value;
}

void MainWindow::clearVectors(){
    this->vectorLongFileNames.clear();
    this->vectorShortFileNames.clear();
    this->vectorExtension.clear();
    this->vectorCodec.clear();
}

void MainWindow::setPropertiesOnQTableWidget(){
    QStringList labels;
    labels << tr("Nombre de archivo") << tr("Extensión") << tr("Codec Name");
    labels << tr("Codec Tag") << tr("Codec Tag2");
    labels << tr("Status");
    //labels << tr("Codec Tag") << tr("Codec Tag2") << tr("Codec Profile");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::setLabelCurrentPathIn(){
    ui->labelCurrentPathIn->setText(QString::fromStdString(this->getCurrentInputPath()));
}

void MainWindow::on_pushButton_clicked()
{
    if(this->getFlagProcessed()){
        QMB_aviso.setWindowTitle(QString::fromStdString("Aviso!"));
        QMB_aviso.setText(QString::fromStdString("La aplicación ya fue procesada, debe reiniciar la aplicación si desea reprocesar!!!"));
        QMB_aviso.exec();
        return;
    }
    int contador = 0;
    QString fileDir;
    fileDir = QFileDialog::getExistingDirectory(this,QString::fromStdString("Selecciona folder de videos"),QDir::currentPath(),QFileDialog::ShowDirsOnly);
    if(!fileDir.isEmpty() && !fileDir.isNull()){
        this->clearVectors();
        this->setCurrentInputPath(fileDir.toStdString());
        this->setCurrentOutputPath(fileDir.toStdString());
        this->setLabelCurrentPathIn();
        QDir directory(fileDir);
        QStringList listVideos = directory.entryList(this->qslValidExtensions,QDir::Files);
        foreach(QString filename, listVideos){
            QString srcFileName = directory.absolutePath()+QDir::toNativeSeparators(QString::fromStdString("/")) + filename;
            //std::cout << QFileInfo(filename).completeSuffix().toStdString() << std::endl;
            this->vectorLongFileNames.push_back(srcFileName);
            this->vectorShortFileNames.push_back(filename);
        }
        foreach(QString filename, this->vectorLongFileNames){
            //std::cout << filename.toStdString() << std::endl;
            QTableWidgetItem *fileNameItem = new QTableWidgetItem(filename);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount() );
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 0, fileNameItem);
            contador++;
        }
        this->setNumberOfVideos(contador);
        ui->labelNumberOfVideos->setText(QString::number(contador));
        /*foreach(QString filename, this->vectorShortFileNames){
            //std::cout << filename.toStdString() << std::endl;
            QTableWidgetItem *fileNameItem = new QTableWidgetItem(filename);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount() );
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 0, fileNameItem);
        }*/
    }
}

QString MainWindow::getCodec(QString filename,QString *codec_tag,QString *codec_tag2,QString *codec_name,QString *codec_profile, QString *codec_description){
    AVCodec *codec;
    AVCodecContext *c= NULL;
    AVFormatContext *pFormatContext = avformat_alloc_context();
    //avformat_open_input(&pFormatContext, "/home/pepe/EJECUTABLES/1805/capturadora_d/local/video/folder_of_chunks/chunk_000000.mp4", NULL, NULL);
    avformat_open_input(&pFormatContext,filename.toStdString().c_str(), NULL, NULL);
    //printf("Format %s, duration %lld us\n", pFormatContext->iformat->long_name, pFormatContext->duration);
    avformat_find_stream_info(pFormatContext,  NULL);
    char buffer[100];
    //std::cout << "nb_streams: " << pFormatContext->nb_streams << std::endl;
    for(int i = 0; i < pFormatContext->nb_streams; i++){
        AVCodecContext *pLocalCodecParameters = pFormatContext->streams[i]->codec;
        AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
        printf("\tCodec %s ID %d bit_rate %lld\n", pLocalCodec->long_name, pLocalCodec->id, pLocalCodecParameters->bit_rate);
        //std::cout << pLocalCodec->name << std::endl;
        //codec_name = QString::fromStdString(pLocalCodec->name);
        //std::cout << pLocalCodecParameters->codec_name << std::endl;
        char a, b, c, d;
        a = pLocalCodecParameters->codec_tag     & 0xff;
        b = pLocalCodecParameters->codec_tag>>8  & 0xff;
        c = pLocalCodecParameters->codec_tag>>16 & 0xff;
        d = pLocalCodecParameters->codec_tag>>24 & 0xff;
        /*printf("codec_tag_string=");
        if (isprint(a)) {
            printf("%c", a);
        }else{
            printf("[%d]", a);

        }
        if(isprint(b)){
            printf("%c", b);
        }else{
            printf("[%d]", b);
        }
        if(isprint(c)){
            printf("%c", c);
        }else{
            printf("[%d]", c);
        }
        if(isprint(d)){
            printf("%c", d);
        }else{
            printf("[%d]", d);
        }*/
        //printf("\ncodec_tag2=0x%04x\n", pLocalCodecParameters->codec_tag);
        //std::cout << std::endl;

        sprintf(buffer,"0x%04x",pLocalCodecParameters->codec_tag);
        //codec_tag = QString::fromStdString("");
//        codec_tag.append(a);
//        codec_tag.append(b);
//        codec_tag.append(c);
//        codec_tag.append(d);
        //codec_tag = QString::fromStdString(char(a))+QString::fromStdString(char(b))+QString::fromStdString(char(c))+QString::fromStdString(char(d));
        //codec_tag2 = QString::fromStdString(buffer);
        if(pFormatContext->nb_streams > 1){
            std::cout << "WARNING: " << "El numero de streams es mayor que 1 " << std::endl;
            break;
        }
    }
    //std::cout << buffer << std::endl;
    avformat_close_input(&pFormatContext);
    avformat_free_context(pFormatContext);
}

QString MainWindow::getCodec(QString filename,char lista_parametros[10][200]){
    QString codec_tag("");
    for(int i = 0;i < 10;++i){
        strcpy(lista_parametros[i],"NaN");
    }
    AVCodec *codec;
    AVCodecContext *c= NULL;
    AVFormatContext *pFormatContext = avformat_alloc_context();
    avformat_open_input(&pFormatContext,filename.toStdString().c_str(), NULL, NULL);
    //printf("Format %s, duration %lld us\n", pFormatContext->iformat->long_name, pFormatContext->duration);
    avformat_find_stream_info(pFormatContext,  NULL);
    char buffer[100];
    for(int i = 0; i < pFormatContext->nb_streams; i++){
        AVCodecContext *pLocalCodecParameters = pFormatContext->streams[i]->codec;
        AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
        //printf("\tCodec %s ID %d bit_rate %lld\n", pLocalCodec->long_name, pLocalCodec->id, pLocalCodecParameters->bit_rate);
        //std::cout << pLocalCodec->name << std::endl;
        //codec_name = QString::fromStdString(pLocalCodec->name);
        //std::cout << pLocalCodecParameters->codec_name << std::endl;
        char a, b, c, d;
        a = pLocalCodecParameters->codec_tag     & 0xff;
        b = pLocalCodecParameters->codec_tag>>8  & 0xff;
        c = pLocalCodecParameters->codec_tag>>16 & 0xff;
        d = pLocalCodecParameters->codec_tag>>24 & 0xff;
        sprintf(buffer,"0x%04x",pLocalCodecParameters->codec_tag);
        strcpy(lista_parametros[0],pLocalCodec->long_name);
        lista_parametros[1][0] = char(a);
        lista_parametros[1][1] = char(b);
        lista_parametros[1][2] = char(c);
        lista_parametros[1][3] = char(d);
        lista_parametros[1][4] = '\0';
        strcpy(lista_parametros[2],buffer);
        codec_tag += QString::fromStdString(buffer);
        strcpy(lista_parametros[3],pLocalCodecParameters->codec_name);
        if(pFormatContext->nb_streams > 1){
            std::cout << "WARNING: " << "El numero de streams es mayor que 1 " << std::endl;
            break;
        }
    }
    avformat_close_input(&pFormatContext);
    avformat_free_context(pFormatContext);
    return codec_tag;
}

void MainWindow::on_pushButtonProcesar_clicked()
{
    if(this->getFlagProcessed()){
        QMB_aviso.setWindowTitle(QString::fromStdString("Aviso!"));
        QMB_aviso.setText(QString::fromStdString("La aplicación ya fue procesada, debe reiniciar la aplicación si desea reprocesar!!!"));
        QMB_aviso.exec();
        return;
    }
    if(this->vectorLongFileNames.size() > 0){
        this->setFlagProcessed(true);
        bool status = false;
        int contador = 0;
        int contadorIncorrect = 0;
        int total = this->vectorLongFileNames.size();
        QString strStatus("incorrect");
        foreach(QString filename, this->vectorLongFileNames){
            QString codec_tag;
            QString codec_tag2;
            QString codec_name;
//            QString codec_profile;
//            QString codec_description;
            this->vectorExtension.push_back(QFileInfo(filename).completeSuffix());
            //this->getCodec(filename,codec_tag,codec_tag2,codec_name,codec_profile,codec_description);
            this->getCodec(filename,lista_parametros);
            std::string aux1 = std::string(lista_parametros[0]);
            std::string aux2 = std::string(lista_parametros[1]);
            std::string aux3 = std::string(lista_parametros[2]);
//            std::string aux4 = std::string(lista_parametros[3]);
//            std::string aux5 = std::string(lista_parametros[4]);
            codec_tag = QString::fromStdString(aux1);
            codec_tag2 = QString::fromStdString(aux2);
            codec_name = QString::fromStdString(aux3);
//            std::cout << ui->tableWidget->rowCount() << "," << ui->tableWidget->columnCount() << std::endl;
            QTableWidgetItem *fileExtensionItem = new QTableWidgetItem(QFileInfo(filename).completeSuffix());
            ui->tableWidget->setItem( contador, 1, fileExtensionItem);
            QTableWidgetItem *fileCodecTagItem = new QTableWidgetItem(codec_tag);
            ui->tableWidget->setItem( contador, 2, fileCodecTagItem);
            QTableWidgetItem *fileCodecTag2Item = new QTableWidgetItem(codec_tag2);
            ui->tableWidget->setItem( contador, 3, fileCodecTag2Item);
            QTableWidgetItem *fileCodecNameItem = new QTableWidgetItem(codec_name);
            ui->tableWidget->setItem( contador, 4, fileCodecNameItem);
//            std::cout << aux1 << ",";
//            std::cout << aux2 << ",";
//            std::cout << aux3 << ",";
            /*
            std::cout << aux4 << ",";
            std::cout << aux5 << std::endl;*/
            std::cout << std::endl;
            this->vectorCodecTag.push_back(codec_tag);
            this->vectorCodecTag2.push_back(codec_tag2);
            this->vectorCodecName.push_back(codec_name);
            this->vectorStatusCorrect.push_back(false);
            status = false;
            if(this->vectorExtension[contador] == "mp4" && codec_tag2 == "avc1"){
                this->vectorStatusCorrect[contador] = true;
                status = true;
            }
            if(status == true){
                strStatus = QString::fromStdString("correct");
            }else{
                strStatus = QString::fromStdString("incorrect");
                contadorIncorrect++;
                ui->labelNumberOfVideosIncorrect->setText(QString::number(contadorIncorrect));
            }
            QTableWidgetItem *fileCodecStatusItem = new QTableWidgetItem(strStatus);
            ui->tableWidget->setItem( contador, 5, fileCodecStatusItem);
            //this->vectorCodecProfile.push_back(codec_profile);
            //this->vectorCodecDescription.push_back(codec_description);
            //QTableWidgetItem *fcni = new QTableWidgetItem(QString::fromStdString("HOLA"));
            //ui->tableWidget->setItem( contador, 4, fcni);
//            std::cout << contador << "," << ui->tableWidget->rowCount() << "," << ui->tableWidget->columnCount() << std::endl;
            int value = (int)((contador/(float)total)*100);
            ui->progressBar->setValue(value);
//            std::cout << "bandera" << std::endl;
            contador++;
            QApplication::processEvents();
            //std::cout << "bandera2" << std::endl;
        }
        ui->progressBar->setValue(100);
        ui->labelNumberOfVideosIncorrect->setText(QString::number(contadorIncorrect));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!this->getFlagProcessed()){
        QMB_aviso.setWindowTitle(QString::fromStdString("Aviso!"));
        QMB_aviso.setText(QString::fromStdString("La aplicación NO ha procesado nada aun!!!"));
        QMB_aviso.exec();
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Guardar reporte como..."), "",
           tr("CSV(*.csv);;All Files (*)"));
    std::cout << fileName.toStdString() << std::endl;
    FILE *out;
    out = fopen(fileName.toStdString().c_str(),"w");
    if(out != NULL){
        int contador = 0;
        foreach(QString filename, this->vectorLongFileNames){
            fprintf(out,"%06d,",contador+1);
            fprintf(out,"%s,",filename.toStdString().c_str());
            fprintf(out,"%s\n",this->vectorCodecTag2[contador].toStdString().c_str());
            fprintf(out,"%s,",this->vectorCodecName[contador].toStdString().c_str());
            fprintf(out,"%s,",this->vectorCodecTag[contador].toStdString().c_str());
            fprintf(out,"%s,",this->vectorExtension[contador].toStdString().c_str());
            if(this->vectorStatusCorrect[contador]){
                fprintf(out,"Correct\n");
            }else{
                fprintf(out,"Incorrect\n");
            }
            contador++;
        }
        fclose(out);
    }
}
