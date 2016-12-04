//
//  main.cpp
//  isosurface
//
//  Created by Mario Díaz on 12/3/16.
//  Copyright © 2016 Mario Díaz. All rights reserved.
//


#include "vtkImageReader.h"
#include "vtkImageViewer.h"
#include "vtkImageMagnify.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

#define IMG_FILE "/Users/MarioDiaz/Desktop/quarter.1"

int main (void)
{
    vtkImageReader *imgReader = vtkImageReader::New();
    imgReader->SetFileDimensionality(2);
    imgReader->SetFileName(IMG_FILE);
    imgReader->SetNumberOfScalarComponents(1);
    imgReader->SetDataExtent(0,63, 0,63, 0,0);
    
    vtkImageMagnify *imgMagnify = vtkImageMagnify::New();
    imgMagnify->SetInputConnection(imgReader->GetOutputPort());
    imgMagnify->SetMagnificationFactors(3, 3, 3);
    
    vtkImageViewer* imgViewer = vtkImageViewer::New();
    imgViewer->SetInputConnection(imgMagnify->GetOutputPort());
    
    vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(imgViewer->GetRenderer());
    renWindow->SetSize(64*3, 64*3);
    
    vtkRenderWindowInteractor *renWindowInteractor = vtkRenderWindowInteractor::New();
    renWindowInteractor->SetRenderWindow(renWindow);
    renWindowInteractor->Initialize();
    renWindowInteractor->Start();
    
    return 0;
}