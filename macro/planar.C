{
   GeFiCa::X *field = new GeFiCa::X;
   field->LoadField("planar1d.root");
   Drift *drift = new Drift(field);
   drift->SetHit(1.0, 2.5, 2.1);
   drift->UpdateTrajectory();
}
