# Bus Simulator 3D - Toulouse Map & Realistic Buses

## 🚋 Trois Types de Bus Réalistes

### 1. **Bus Standard Urbain** (12m)
- **Modèles**: Mercedes-Benz Citaro, Volvo B7
- **Capacité**: 100 passagers (60 assis, 40 debout)
- **Dimensions**: 12m x 2.5m x 3.5m
- **Masses**: ~12 tonnes
- **Caractéristiques**:
  - 3 portes d'accès
  - Suspension pneumatique
  - Moteur de 300 kW
  - Transmission automatique 6 vitesses

### 2. **Bus Articulé** (18m)
- **Modèles**: Mercedes-Benz Citaro G, Volvo B12M
- **Capacité**: 160 passagers
- **Dimensions**: 18m x 2.5m x 3.5m
- **Masses**: ~18 tonnes
- **Caractéristiques**:
  - 4-5 portes d'accès
  - Articulation flexible
  - Section avant et remorque
  - Freinage électronique avancé

### 3. **Mini-Bus** (10m)
- **Modèles**: Irisbus Cristalis, MAN Lion's City M
- **Capacité**: 50 passagers
- **Dimensions**: 10m x 2.3m x 3.2m
- **Masses**: ~7.5 tonnes
- **Caractéristiques**:
  - 2 portes
  - Plus maniéable dans les rues étroites
  - Accés facilité pour PMR
  - Moteur plus compact

---

## 📍 Map de Toulouse - Reproduction Réaliste

### [🦭 Zones Incluses

#### **Vieux Toulouse**
- Ruelles médiévales étroites
- Briques rouges caractéristiques
- Déniveaués et courées historiques
- Défi de navigation pour le bus

#### **Place du Capitole**
- Grande place urbaine
- Facade renaissance du Capitole
- Voies à sens unique
- Station de bus RATP

#### **Pont Neuf**
- Pont historique sur la Garonne
- Routes d'accès et pentes
- Pont piétonnier
- Beaux points de vue

#### **Allée Jules Michelet**
- Grande avenue commerciale
- Espaces de circulation variés
- Rond-points et carrefours
- Trottoirs de qualité

#### **Zone Aérospatiale (Aeroparc)**
- Zone industrielle moderne
- Routes larges et rectilignes
- Rond-point important
- Paysage moins dénsé

#### **Quartier Bayonne**
- Résidentiel avec petites rues
- Espérances résidéntiels
- Parcs et espaces verts
- Moins frequentisé

### 🚗 Système de Routes

- **Routes principales**: 15m de large (2 voies + stationnement)
- **Routes secondaires**: 10m de large
- **Ruelles**: 6-8m de large
- **Trottoirs**: 1.5-3m
- **Marquages routiers**: Fidèles à la France

### 🏁 Points d'Intérêt

- **Stations de bus RATP**: Arrêts réalistes
- **Feux tricolores**: Système de circulation complet
- **Lampadaires urbains**: Réalistes avec éclairage
- **Arbres et végétation**: Ambiancer urbain naturel
- **Voitures de traffic**: Circulation urbaine

### 🎨 Visuels & Matériaux

#### **Briques de Toulouse**
- Couleur: #B44646 (rouge de brique)
- Matériau: Briques de terre cuite réalistes
- Vieillissement: Patine naturelle sur les bâtiments anciens

#### **Routes**
- Texture asphalte réaliste
- Marquages blancs et jaunes
- Usure réaliste
- Puddles d'eau (après pluie)

#### **Ciel & Lumière**
- Cycle jour/nuit
- Ombre dynamique
- Ciel nuageux réaliste
- Climat toulousain (méditerranéen modifié)

---

## 📊 Données Techniques

### Dimensions Map
- **Largueur**: 2000m
- **Longueur**: 2000m
- **Zone de controle**: 4 km²

### Densité de Bâtiments
- Vieux Toulouse: 90% d'occupation
- Centre urbain: 70% d'occupation
- Zone residentielle: 40% d'occupation
- Zone industrielle: 20% d'occupation

### Performance
- Level Streaming pour chargement optimisé
- Occlusion culling pour FPS stable
- LOD pour bâtiments lointains
- 60 FPS cible sur configs mid-range

---

## 🚀 Installation et Utilisation

### 1. Sélectionner le Type de Bus
```cpp
// Dans l'éditeur Unreal
// Placer l'un des trois blueprints:
// - BP_BusStandard
// - BP_BusArticulated  
// - BP_BusMini
```

### 2. Charger la Map
```cpp
// Ouvrir la map Toulouse
// Content/Maps/Toulouse_Main
```

### 3. Démarrer la Simulation
- Position du bus: Zone de départ prédéfinie
- Itinéraire: Routes principales par défaut
- Trafic: Voitures IA déjà générées

---

## 👤 Références et Sources

- **Maps**: Google Earth, OSM (OpenStreetMap)
- **Bus Models**: Désaccord visée, données constructeurs
- **Textures**: Photogrammétrie de vrais sites toulousains
- **Références**: RATP, TLS (Toulouse Transport)

---

**Profitez de votre expérience de conduite de bus à Toulouse !** 🎉
