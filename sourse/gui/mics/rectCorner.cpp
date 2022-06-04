#include "../../../headers/gui/mics/rectCorner.hpp"

void Corner::GetRoundRectPath(GraphicsPath* pPath, Rect r, int dia)
{
	// diameter can't exceed width or height
	if (dia > r.Width)    dia = r.Width;
	if (dia > r.Height)    dia = r.Height;

	// define a corner 
	Rect Corner(r.X, r.Y, dia, dia);

	// begin path
	pPath->Reset();

	// top left
	pPath->AddArc(Corner, 180, 90);

	// tweak needed for radius of 10 (dia of 20)
	if (dia == 20)
	{
		Corner.Width += 1;
		Corner.Height += 1;
		r.Width -= 1; r.Height -= 1;
	}

	// top right
	Corner.X += (r.Width - dia - 1);
	pPath->AddArc(Corner, 265, 90);

	// bottom right
	Corner.Y += (r.Height - dia - 1);
	pPath->AddArc(Corner, 0, 90);

	// bottom left
	Corner.X -= (r.Width - dia - 1);
	pPath->AddArc(Corner, 85, 90);

	// end path
	pPath->CloseFigure();
}

void Corner::DrawRoundRect(Graphics* pGraphics, Rect r, Color color, int radius, int width)
{
	int dia = 2 * radius;

	// set to pixel mode
	int oldPageUnit = pGraphics->SetPageUnit(UnitPixel);

	// define the pen
	Pen pen(color, 1);
	pen.SetAlignment(PenAlignmentCenter);

	// get the corner path
	GraphicsPath path;

	// get path
	GetRoundRectPath(&path, r, dia);

	// draw the round rect
	pGraphics->DrawPath(&pen, &path);

	// if width > 1
	for (int i = 1; i < width; i++)
	{
		// left stroke
		r.Inflate(-1, 0);
		// get the path
		GetRoundRectPath(&path, r, dia);

		// draw the round rect
		pGraphics->DrawPath(&pen, &path);

		// up stroke
		r.Inflate(0, -1);

		// get the path
		GetRoundRectPath(&path, r, dia);

		// draw the round rect
		pGraphics->DrawPath(&pen, &path);
	}

	// restore page unit
	pGraphics->SetPageUnit((Unit)oldPageUnit);
}

void Corner::FillRoundRect(Graphics* pGraphics, Brush* pBrush, Rect r, Color border, int radius)
{
	/*pGraphics->SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);
	pGraphics->SetCompositingMode(CompositingMode::CompositingModeSourceOver);
	pGraphics->SetPixelOffsetMode(PixelOffsetMode::PixelOffsetModeHighQuality);
	pGraphics->SetInterpolationMode(InterpolationMode::InterpolationModeHighQuality);
	pGraphics->SetCompositingQuality(CompositingQuality::CompositingQualityHighQuality);*/
	int dia = 2 * radius;

	// set to pixel mode
	int oldPageUnit = pGraphics->SetPageUnit(UnitPixel);

	// define the pen
	Pen pen(border, 2);
	if (radius != 3)
	{
		pen.SetAlignment(PenAlignmentCenter);
	}

	// get the corner path
	GraphicsPath path;

	// get path
	GetRoundRectPath(&path, r, dia);

	// fill
	pGraphics->FillPath(pBrush, &path);

	// draw the border last so it will be on top
	if (radius != 3)
	{
		pGraphics->DrawPath(&pen, &path);
	}

	// restore page unit

}
