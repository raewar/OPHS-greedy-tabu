#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <utility>
#include <math.h>

using namespace std;

/*Obtiene la distancia euclidiana entre 2 puntos
Input: coordenadas de los dos puntos
Return: la distancia
*/
float getDistancia(int x1, int y1, int x2, int y2){
	int h1, h2;
	float dist;
	h1 = abs(x1-x2);
	h2 = abs(y1-y2);
	dist = pow(h1,2) + pow(h2,2);
	dist = sqrt(dist);
	return dist;
}
/*Verifica que un hotel/POI existe en la solucion actual.
Input: Nombre del hotel/POI, vector solucion
Retorna True si existe, false si lo contrario.
*/
bool existe_en_sol(string str, vector<pair<string, float> > sol){
	for(auto i = sol.begin(); i!=sol.end(); i++){
		if(i->first == str){
			return true;
		}
	}
	return false;
}
/*Obtiene el puntaje total de una solucion especifica
Input: Vector solucion, map de los puntajes
Retorna: un int de puntaje
*/
int getPuntaje(vector<pair<string, float> >& solucion, map<string, int>& puntaje){
	int puntos = 0;
	for(auto i = solucion.begin(); i!=solucion.end(); i++){
		puntos += puntaje[i->first];
	}
	return puntos;
}
/*Obtiene un Hotel/POI mas cercano a un punto dado, buscando en todo el entorno
Input: Coordenadas x,y del punto fijo, map de los POI/Hoteles, vector de solucion
Retorna: un elemento de solución (POI, distancia)
*/
pair<string, float> getPuntoMasCercano(int x, int y, map<string, pair<int, int> > punto, vector<pair<string, float> > camino){

	float min = 99999.;
	string min_s = "";
	float aux = 0.;
	for(auto i = punto.begin(); i!=punto.end(); i++){
		if(!existe_en_sol(i->first,camino)){
			aux = getDistancia(x,y,get<0>(i->second),get<1>(i->second));
			if(min > aux ){
				min = aux;
				min_s = i->first;
			}
		}
	}
	return make_pair(min_s, min);
}
/*Obtiene la distancia de un punto (x,y) al ultimo hotel (h1)
Input: Coordenadas x,y del punto fijo, map con los hoteles *hoteles Inicio/Fin, no Extras*
Retorna: un elemento de solución (POI, distancia)
*/
pair<string, float> getDistanciaUltimoHotel(int x, int y, map<string, pair<int, int> > hoteles){
	auto i = hoteles.end();
	i--;
	return make_pair("h1", getDistancia(x,y,get<0>(i->second), get<1>(i->second))) ;
}


/*

*/
void actualizarDistancias(vector<pair<string, float> >& sol_actual, map<string, pair<int, int> > POI, map<string, pair<int, int> > Hoteles, 
	map<string, pair<int, int> > InFn, map<string, pair<int, int> > HPOI, vector<float>& tiempo_trip){

	auto ItActual1 = sol_actual.begin();
	float dist1 = 0;
	int trip = 0;
	bool flag = false;

	for(ItActual1 = sol_actual.begin(); ItActual1 != sol_actual.end()-1; ItActual1++){
		
		if( InFn.find(ItActual1->first) != InFn.end() ){
			if(InFn.find((ItActual1+1)->first) != InFn.end()){
				dist1 = getDistancia(get<0>(InFn[ItActual1->first]), get<1>(InFn[ItActual1->first]), get<0>(InFn[(ItActual1+1)->first]), get<1>(InFn[(ItActual1+1)->first]));
			}
			else if(Hoteles.find((ItActual1+1)->first) != Hoteles.end()){
				dist1 = getDistancia(get<0>(InFn[ItActual1->first]), get<1>(InFn[ItActual1->first]), get<0>(Hoteles[(ItActual1+1)->first]), get<1>(Hoteles[(ItActual1+1)->first]));
			}
			else{
				dist1 = getDistancia(get<0>(InFn[ItActual1->first]), get<1>(InFn[ItActual1->first]), get<0>(POI[(ItActual1+1)->first]), get<1>(POI[(ItActual1+1)->first]));
			}
			//cout << "distancia entre " << ItActual1->first << " y " << (ItActual1+1)->first << " es: " << dist1 << "\n";
			ItActual1->second = dist1;
		}

		else if( POI.find(ItActual1->first) != POI.end() ){
			
			if(InFn.find((ItActual1+1)->first) != InFn.end()){
				dist1 = getDistancia(get<0>(POI[ItActual1->first]), get<1>(POI[ItActual1->first]), get<0>(InFn[(ItActual1+1)->first]), get<1>(InFn[(ItActual1+1)->first]));
			}
			else if(Hoteles.find((ItActual1+1)->first) != Hoteles.end()){
				dist1 = getDistancia(get<0>(POI[ItActual1->first]), get<1>(POI[ItActual1->first]), get<0>(Hoteles[(ItActual1+1)->first]), get<1>(Hoteles[(ItActual1+1)->first]));

			}
			else{
				dist1 = getDistancia(get<0>(POI[ItActual1->first]), get<1>(POI[ItActual1->first]), get<0>(POI[(ItActual1+1)->first]), get<1>(POI[(ItActual1+1)->first]));
			}
			//cout << "distancia entre " << ItActual1->first<< " y " << (ItActual1+1)->first << " es: " << dist1 << "\n";
			ItActual1->second = dist1;

		}
		else{
			if(InFn.find((ItActual1+1)->first) != InFn.end()){
				dist1 = getDistancia(get<0>(Hoteles[ItActual1->first]), get<1>(Hoteles[ItActual1->first]), get<0>(InFn[(ItActual1+1)->first]), get<1>(InFn[(ItActual1+1)->first]));
				
			}
			else if(Hoteles.find((ItActual1+1)->first) != Hoteles.end()){
				dist1 = getDistancia(get<0>(Hoteles[ItActual1->first]), get<1>(Hoteles[ItActual1->first]), get<0>(Hoteles[(ItActual1+1)->first]), get<1>(Hoteles[(ItActual1+1)->first]));
				
			}
			else{
				dist1 = getDistancia(get<0>(Hoteles[ItActual1->first]), get<1>(Hoteles[ItActual1->first]), get<0>(POI[(ItActual1+1)->first]), get<1>(POI[(ItActual1+1)->first]));
			}
			//cout << "distancia entre " << ItActual1->first<< " y " << (ItActual1+1)->first << " es: " << dist1 << "\n";
			ItActual1->second = dist1;
			
		}
		dist1 = 0;
 	}

	float sum = 0;
	trip = 0;
	for(ItActual1 = sol_actual.begin(); ItActual1 != sol_actual.end(); ItActual1++){
		if( Hoteles.find((ItActual1)->first) != Hoteles.end() || ItActual1->first == "h1" ){
			tiempo_trip.at(trip) = sum;
			sum = 0;
			trip++;
		}
		sum += ItActual1->second;
	}

}
/*Movimiento Tabu de inserción
A una solucion especifica, se "intenta" agregar un POI entre 2 POIs existentes, donde la distancia
del Trip maxima no sea superada. En caso de que se inserte, se agrega a la lista tabu.
Input: Vector de solucion inicial,  map de la lista tabu, map de los POIS, map de los Hoteles Inicial/Final, 
un map de todos los POI/Hoteles extras, la vida de los elementos tabus.
Retorna: un vector solucion con 0 o mas puntos agragados.
*/
bool tabuInsert(vector<pair<string, float> >& sol_actual, 
	map<string, int>& lista_tabu, map<string, pair<int, int> > POI, map<string, pair<int, int> > Hoteles, 
	map<string, pair<int, int> > InFn, map<string, pair<int, int> > HPOI, int vida_tabu, vector<float>& tiempo_trip, vector<float> Ttrips){

	auto ItActual1 = sol_actual.begin();
	auto ItActual2 = ItActual1;
	float dist1, dist2, diff;
	pair<string, float> punto_cercano;
	bool insertado = false;
	int trip = 0; // trip inicial


	for(ItActual1; ItActual1 != sol_actual.end(); ItActual1++){
		ItActual2 = ItActual1+1;

		if(ItActual1->first == "h1"){
			break;
		}
		if( Hoteles.find(ItActual1->first) != Hoteles.end() ){ //hotel
			trip++;
		}
		if( HPOI.find(ItActual1->first) != HPOI.end() || InFn.find(ItActual1->first) != InFn.end() ){ //It1 es un POI
			for(auto IPOI = POI.begin(); IPOI != POI.end(); IPOI++){
				if(!existe_en_sol(IPOI->first, sol_actual)){
					
					if(InFn.find(ItActual1->first)!=InFn.end() && InFn.find(ItActual2->first)==InFn.end()){

						dist1 = getDistancia(get<0>(IPOI->second), get<1>(IPOI->second), get<0>(InFn[ItActual1->first]), get<1>(InFn[ItActual1->first]));
						dist2 = getDistancia(get<0>(IPOI->second), get<1>(IPOI->second), get<0>(HPOI[ItActual2->first]), get<1>(HPOI[ItActual2->first]));
					}
					else if(InFn.find(ItActual2->first)!=InFn.end() && InFn.find(ItActual1->first)==InFn.end()){

						dist1 = getDistancia(get<0>(IPOI->second), get<1>(IPOI->second), get<0>(HPOI[ItActual1->first]), get<1>(HPOI[ItActual1->first]));
						dist2 = getDistancia(get<0>(IPOI->second), get<1>(IPOI->second), get<0>(InFn[ItActual2->first]), get<1>(InFn[ItActual2->first]));
					}
					else{

						dist1 = getDistancia(get<0>(IPOI->second), get<1>(IPOI->second), get<0>(HPOI[ItActual1->first]), get<1>(HPOI[ItActual1->first]));
						dist2 = getDistancia(get<0>(IPOI->second), get<1>(IPOI->second), get<0>(HPOI[ItActual2->first]), get<1>(HPOI[ItActual2->first]));
					}


					diff = Ttrips.at(trip) - tiempo_trip.at(trip);
					//cout << "evaluacion: " << IPOI->first << " diff+second: " << ItActual1->second + diff << " dist1+dist2: " << dist1 + dist2 << "\n";
 					

					if((dist1 + dist2 <= ItActual1->second + diff) && lista_tabu.find(IPOI->first) == lista_tabu.end()){

						sol_actual.insert(ItActual2 , make_pair(IPOI->first, dist2));
						lista_tabu.insert({IPOI->first, vida_tabu});
						return true;
						
					}
				}
			}
		}

	}
	return false;
}
/*Movimiento Tabu de borrado
A una solucion especifica, se le elimina el POI con menos puntaje; si hay mas de 1, elige aleatoriamente.
Input: Vector de solucion inicial,  map de la lista tabu, map de los POIS, un map con los puntajes de los POI, 
un map de todos los POI/Hoteles extras, la vida de los elementos tabus.
Retorna:
*/
bool tabuDelete(vector<pair<string, float> >& sol_actual, 
	map<string, int>& lista_tabu, map<string, pair<int, int> > POI, map<string, pair<int, int> > Hoteles, map<string, pair<int, int> > InFn, 
	map<string, int> POI_v, map<string, pair<int, int> > HPOI, int vida_tabu, vector<float> tiempo_trip){

	auto ItActual1 = sol_actual.begin();
	vector<pair<string, int> > puntos;
	vector<pair<string, int> > puntos_minimos;
	int min = 9999;
	bool borrado = false;
	int trip = 0;

	for(ItActual1; ItActual1 != sol_actual.end(); ItActual1++){

		if(POI.find(ItActual1->first) != POI.end() && lista_tabu.find(ItActual1->first) == lista_tabu.end()) { 
			if(min > POI_v[ItActual1->first]){
				min = POI_v[ItActual1->first];
			}
			puntos.push_back({ItActual1->first, trip});
		}
		else if(Hoteles.find(ItActual1->first) != Hoteles.end()){
			trip++;
		}
	}
	if(min == 9999){
		return false;
	}

	int count = 0;

	for(auto i = puntos.begin(); i!= puntos.end(); i++){
		if(POI_v[i->first] == min){
			puntos_minimos.push_back({i->first, i->second});
		}
	}

	auto k = puntos_minimos.begin();

	if(puntos_minimos.size() > 1){
		int nrand = rand() % puntos_minimos.size();
		k = puntos_minimos.begin() + nrand;
	}
	else{
		k = puntos_minimos.begin();
	}

	for(auto j = sol_actual.begin(); j!=sol_actual.end(); j++){
		if(j->first == k->first){

			sol_actual.erase(j); //posicion donde está
			j--;
			j->second = getDistancia(get<0>(HPOI[(j)->first]), get<0>(HPOI[(j)->first]) , get<0>(HPOI[(j+1)->first]), get<1>(HPOI[(j+1)->first]));

			actualizarDistancias(sol_actual, POI, Hoteles, InFn, HPOI, tiempo_trip);

			lista_tabu.insert({k->first, vida_tabu});

		}
	}

	return true;
}
/*Obtiene el tiempo utilizado de cada trip de una solucion dada
Input: Vector de solucion inicial, map de los POIS, map de los Hoteles extras, map de los Hoteles Inicial/Final.
Retorna: un vector con los tiempos de cada trip
*incompleto*
*/
vector<float> getTiemposTrips(vector<pair<string, float> >& sol_actual, map<string, pair<int, int> > POI, map<string, 
	pair<int, int> > Hoteles, map<string, pair<int, int> > InFn){

	vector<float> tiempos;
	for(auto i = sol_actual.begin(); i!= sol_actual.end(); i++){

	}
}
/*Disminuye en 1 la vida de los elementos en la lista tabu. Si la vida llega a 0, se elimina de la lista
Input: map de la lista tabu
*/
void cicloTabu(map<string, int>& lista_tabu){
	for(auto i = lista_tabu.begin(); i!=lista_tabu.end(); i++){
		i->second -= 1;
		if(i->second <= 0){
			lista_tabu.erase(i->first);
		}
	}

}

/*Movimiento Tabu de swap de POIs
A una solucion especifica, se intercambian 2 POIs de posicion
*incompleto*
Retorna: un vector solucion con 2 elementos cambiados
*/
bool tabuPOISwap(vector<pair<string, float> >& sol_actual, 
	map<string, int>& lista_tabu, map<string, pair<int, int> > POI, map<string, 
	pair<int, int> > Hoteles, map<string, pair<int, int> > InFn, map<string, pair<int, int> > HPOI, int vida_tabu, vector<float>& tiempo_trip){

	vector<pair<string, float> > sol_eval = sol_actual;
	vector<float> tiempo_trip_eval = tiempo_trip;

	auto ItActual1 = sol_eval.begin();
	auto ItActual2 = ItActual1+1;
	float sum = 0;
	float Tour = 0;
	for(auto j = tiempo_trip.begin(); j!=tiempo_trip.end(); j++){
		Tour += *j;
	}

	string nombre1, nombre2;

	for(ItActual1; ItActual1!=sol_eval.end()-1; ItActual1++){
		ItActual2 = ItActual1+1;
		if(POI.find(ItActual1->first) != POI.end()){

			for(ItActual2; ItActual2!=sol_eval.end(); ItActual2++){
				if(POI.find(ItActual2->first) != POI.end()){
					nombre1 = ItActual1->first;
					nombre2 = ItActual2->first;
					ItActual1->first = nombre2;
					ItActual2->first = nombre1;
					actualizarDistancias(sol_eval, POI, Hoteles, InFn, HPOI, tiempo_trip_eval);

					for(auto i = tiempo_trip_eval.begin(); i!=tiempo_trip_eval.end(); i++){
						sum += *i;
					}

					if(sum <= Tour && lista_tabu.find(ItActual1->first) == lista_tabu.end() && lista_tabu.find(ItActual2->first) == lista_tabu.end()){
						//cout << ItActual1->first << " " << ItActual2->first << "\n";

						sol_actual = sol_eval;
						tiempo_trip = tiempo_trip_eval;
						lista_tabu.insert({ItActual1->first, vida_tabu-1});
						lista_tabu.insert({ItActual2->first, vida_tabu});
						return true;
					}
					else{
						ItActual1->first = nombre1;
						ItActual2->first = nombre2;
						sum = 0;
					}
				}
			}
		}
	}

	return false;
}


bool tabuHotelSwap(vector<pair<string, float> >& sol_actual, 
	map<string, int>& lista_tabu, map<string, pair<int, int> > POI, map<string, 
	pair<int, int> > Hoteles, map<string, pair<int, int> > InFn, map<string, pair<int, int> > HPOI, int vida_tabu, vector<float>& tiempo_trip){

	vector<pair<string, float> > sol_eval = sol_actual;
	vector<float> tiempo_trip_eval = tiempo_trip;

	auto ItActual1 = sol_eval.begin();
	float sum = 0;
	float Tour = 0;
	string nombre1, nombre2;

	if(Hoteles.size() <= 1){
		return false;
	}

	for(auto j = tiempo_trip.begin(); j!=tiempo_trip.end(); j++){
		Tour += *j;
	}

	for( ItActual1; ItActual1!=sol_eval.end(); ItActual1++ ){

		if( Hoteles.find(ItActual1->first) != Hoteles.end() ){

			for( auto ItActual2 = Hoteles.begin(); ItActual2!=Hoteles.end(); ItActual2++ ){

				if( !existe_en_sol(ItActual2->first, sol_eval) ){

					nombre1 = ItActual1->first;
					nombre2 = ItActual2->first;

					ItActual1->first = nombre2;
					actualizarDistancias(sol_eval, POI, Hoteles, InFn, HPOI, tiempo_trip_eval);

					for(auto i = tiempo_trip_eval.begin(); i!=tiempo_trip_eval.end(); i++){
						sum += *i;
					}

					if(sum <= Tour && lista_tabu.find(ItActual1->first) == lista_tabu.end() && lista_tabu.find(ItActual2->first) == lista_tabu.end()){
						//cout << ItActual1->first << " " << ItActual2->first << "\n";

						sol_actual = sol_eval;
						tiempo_trip = tiempo_trip_eval;
						lista_tabu.insert({ItActual1->first, vida_tabu-1});
						lista_tabu.insert({ItActual2->first, vida_tabu});
						return true;
					}
					else{
						ItActual1->first = nombre1;
						sum = 0;
					}
				}
			}
		}
	}

	return false;
}

float tiempo_total_trips(vector<float> tiempo_trip){
	float sum_t = 0;
	for(auto i = tiempo_trip.begin(); i!=tiempo_trip.end(); i++){
		sum_t += *i;
	}
	return sum_t;
}




int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	srand (time(NULL));

	//Lectura del archivo por referencia
	//Se sigue el formato, nada que comentar ._.
	int n,h,d,x,y,sn, aux;
	string in;
	float auxf, Tmax;
	vector<float> Ttrips;
	map<string, pair<int, int> > Hoteles, POI, InFn, HPOI;
	map<string, int> POI_v;
	vector<float> tiempo_trip;

	cin >> n >> h >> d >> Tmax;

	while(d--){
		cin >> auxf;
		Ttrips.push_back(auxf);
		tiempo_trip.push_back(0);
	}
	aux = 0;
	while(aux < 2){
		cin >> x >> y >> sn;
		in = "h"+to_string(aux);
		InFn[in] = make_pair(x,y);
		aux++;
	}
	aux = 2;
	while(aux < h+2){
		cin >> x >> y >> sn;
		in = "h"+to_string(aux);
		Hoteles[in] = make_pair(x,y);
		HPOI[in] = make_pair(x,y);
		aux++;
	}
	aux = 0;
	while(aux < n-2){
		cin >> x >> y >> sn;
		in = "s"+to_string(aux);
		POI[in] = make_pair(x,y);
		HPOI[in] = make_pair(x,y);
		POI_v.insert({in, sn});
		aux++;
	}

	/*Algoritmo Greedy

	*/
	vector<pair<string, float> > solI;

	pair<string, float> punto_cercano;
	pair<string, float> hotel_cercano;


	float dist_ac = 0;

	solI.push_back(make_pair("h0", 0)); // agrega el primer hotel
	auto itsolI = solI.begin();


	for( int trip = 0; trip < Ttrips.size(); trip++ ){
		if( trip != Ttrips.size()-1 ){
			if( InFn.find(itsolI->first) != InFn.end() ){
				hotel_cercano = getPuntoMasCercano(InFn.at(itsolI->first).first, InFn.at(itsolI->first).second,  Hoteles, solI);
			}
			else{
				hotel_cercano = getPuntoMasCercano(HPOI.at(itsolI->first).first, HPOI.at(itsolI->first).second,  Hoteles, solI);
			}

			//cout << "distuancia entre "<< hotel_cercano.first << "y " << itsolI->first << "es: " << hotel_cercano.second<< "\n";
			itsolI->second = get<1>(hotel_cercano);
			solI.push_back(make_pair(get<0>(hotel_cercano), 0));
		}
		else{
			hotel_cercano = getDistanciaUltimoHotel( Hoteles.at(itsolI->first).first , Hoteles.at(itsolI->first).second,  InFn);
			itsolI->second = get<1>(hotel_cercano);
			solI.push_back(make_pair(get<0>(hotel_cercano), 0));
		}

		itsolI = solI.end()-1;
	}

	actualizarDistancias(solI, POI, Hoteles, InFn, HPOI, tiempo_trip);


	//Datos de sintonizacion
	int vida_tabu = 0;
	map<string, int> lista_tabu;

	while(tabuInsert(solI, lista_tabu, POI, Hoteles, InFn, HPOI, vida_tabu, tiempo_trip, Ttrips)){
		
		actualizarDistancias(solI, POI, Hoteles, InFn, HPOI, tiempo_trip);
	}

	lista_tabu.clear();

	/*Tabu search
	A una solucion, se le aplican movimientos y se registran las mejorias

	*/
	vector<pair<string, float> > sol_actual = solI;
	vector<pair<string, float> > mejor_sol = solI;
	vector<float> mejor_tiempo_trip = tiempo_trip;


	vector<pair<string, float> > sol_eval = solI;
	int puntaje_actual = getPuntaje(solI, POI_v);
	int puntaje_movimiento;
	int tabu_cont = 0;

	vida_tabu = 15;

	int max = 0;
	vector<pair<string, float> > mejor;

	//Ciclo tab

	for(auto k = 0; k < 3000 ; k++){

		if(tabuInsert(sol_eval, lista_tabu, POI, Hoteles, InFn, HPOI, vida_tabu, tiempo_trip, Ttrips)){
			actualizarDistancias(sol_eval, POI, Hoteles, InFn, HPOI, tiempo_trip);
			//cout << "inserta ";
		}
		else{
			if(tabuPOISwap(sol_eval, lista_tabu, POI, Hoteles, InFn, HPOI, vida_tabu, tiempo_trip)) {
				actualizarDistancias(sol_eval, POI, Hoteles, InFn, HPOI, tiempo_trip);
				//cout << "poiswap ";
			}
			else if(tabuHotelSwap(sol_eval, lista_tabu, POI, Hoteles, InFn, HPOI, vida_tabu, tiempo_trip) ){
				actualizarDistancias(sol_eval, POI, Hoteles, InFn, HPOI, tiempo_trip);
				//cout << "hotalswap ";
			}
			else{
				tabuDelete(sol_eval, lista_tabu, POI, Hoteles, InFn, POI_v, HPOI ,vida_tabu, tiempo_trip);
				actualizarDistancias(sol_eval, POI, Hoteles, InFn, HPOI, tiempo_trip);
				//cout << "tabudelete ";
			}
		}

		if(max < getPuntaje(sol_eval, POI_v) && tiempo_total_trips(tiempo_trip) <= Tmax){
			max = getPuntaje(sol_eval, POI_v);
			mejor_sol = sol_eval;
			mejor_tiempo_trip = tiempo_trip;
		}
		cicloTabu(lista_tabu);
	}

	//procesamiento de salida
	cout << max << "\n";

	float sum_t = 0;
	for(auto i = mejor_tiempo_trip.begin(); i!=mejor_tiempo_trip.end(); i++){
		sum_t += *i;
	}
	cout << sum_t << "\n"; 
	vector<vector<string> > tripis;

	int pos_vec = 0;
	for(auto i = mejor_sol.begin(); i!=mejor_sol.end(); i++){

		if( POI.find(i->first) != POI.end() ){
			(tripis.at(pos_vec)).push_back(i->first);
		}
		else if( Hoteles.find(i->first) != Hoteles.end() ){
			(tripis.at(pos_vec)).push_back(i->first);
			pos_vec++;
			tripis.push_back({});
			(tripis.at(pos_vec)).push_back(i->first);
		}
		else{
			if(i->first == "h1"){
				(tripis.at(pos_vec)).push_back("h1");
				break;
			}
			else{
				tripis.push_back({});
				(tripis.at(pos_vec)).push_back("h0");
			}
		}
	}
	auto cont = 0;
	for(auto i = tripis.begin(); i != tripis.end(); i++){
		cout << Ttrips.at(cont) << " " << mejor_tiempo_trip.at(cont) << " ";

		for(auto j = i->begin(); j != i->end(); j++){
			if(j == i->begin() ){
				cout << *j << " " << i->back() << " ";
			}
			else if(j == i->end()-1){
				break;
			}
			else{
				cout << *j << " ";
			}
			
		}
		cont ++;

		cout << "\n";
	}


	return 0;
}