#include "SFApp.h"

SFApp::SFApp() : fire(0), is_running(true) {

  surface = SDL_GetVideoSurface();
  app_box = make_shared<SFBoundingBox>(Vector2(surface->w/2, surface->h/2), surface->w/2, surface->h/2);
  player  = make_shared<SFAsset>(SFASSET_PLAYER);
  auto player_pos = Point2(surface->w/2, 100.0f);
  player->SetPosition(player_pos);

  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN);
    auto pos   = Point2((surface->w/number_of_aliens) * i, 900.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

  auto coin = make_shared<SFAsset>(SFASSET_COIN);
  auto coin_pos  = Point2((surface->w/2), 480);
  coin->SetPosition(coin_pos);
  coins.push_back(coin);

  // auto barrier = make_shared<SFAsset>(SFASSET_BARRIER);
  // auto barrier_pos = Point2(0, 200);
  // barrier->SetPosition(barrier_pos);
  // barrier.push_back(barrier);
}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    cout << "YOU GOT " << score << " POINTS!!" << endl;
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;
  case SFEVENT_FIRE:
    fire ++;
    std::stringstream sstm;
    sstm << "Fire " << fire;
    SDL_WM_SetCaption(sstm.str().c_str(),  sstm.str().c_str());
    FireProjectile();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
  }

  for(auto c: coins) {
    c->GoSouth();
  }

  // Update enemy positions
  for(auto a : aliens) {
    // do something here
    a ->GoSouth();
  }

  // Detect collisions
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
        score += 100;
        p->HandleCollision();
        a->HandleCollision();
        if(fire == 100){
          cout << "YOU GOT " << score << " POINTS!!" << endl;
          is_running = false;
        }
      }
    }
  }

  for(auto c : coins) {    
      if(c->CollidesWith(player)) {
        score += 50;
        c->HandleCollision();
        player->HandleCollision();
      }    
  }

  for(auto a : aliens) {    
      if(a->CollidesWith(player)) {
        score -= 50;
        a->HandleCollision();
        player->HandleCollision();
        cout << "YOU WERE KILLED IN ACTION! But scored " << score << " Points" << endl;
        is_running = false;
      }    
  }

     list<shared_ptr<SFAsset>> tmp1;
  for(auto c : coins) {
    if(c->IsAlive()) {
      tmp1.push_back(c);
    }
  }
  coins.clear();
  coins = list<shared_ptr<SFAsset>>(tmp1);

  if(aliens.size() < maxAliens){
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN);
    auto pos   = Point2(rand()%(surface->w)+1, (surface->h)+100);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

  //If mine goes off screen needs to be killed!


  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);

}

void SFApp::OnRender() {
  // clear the surface
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 8, 54, 129) );

  // draw the player
  player->OnRender(surface);

  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender(surface);}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender(surface);}
  }

  for(auto c: coins) {
    if(c->IsAlive()) {c->OnRender(surface);};
  }

  // Switch the off-screen buffer to be on-screen
  SDL_Flip(surface);
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
